/* 
 * queue.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-10-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

typedef struct element {
	struct element *next;
	void* val_p;//pointer to something in q
} element_t;

typedef struct queue {
	element_t *front;
	element_t *back;                                                         
} iqueue_t;



queue_t* open(void){
	iqueue_t *newQueue = malloc(sizeof(iqueue_t));
    
    if (newQueue == NULL) {
        return NULL;
    }
    newQueue->front = NULL;
    newQueue->back = NULL;

    return (queue_t*)newQueue;
}

void qclose(queue_t* qp){
	iqueue_t* iqp = (iqueue_t*)(qp);
	if(iqp == NULL){
		return;
	}

	while (iqp->front != NULL) {
		iqueue_t *temp = iqp->front;
		iqp->front = iqp->front->next;
		free(temp);
	}
	free(iqp);
}

int32_t qput(queue_t *qp, void *elementp){
	if (qp == NULL || elementp == NULL) {
        return -1; // Nonzero value for failure
    }

    // Cast the queue_t pointer to an iqueue_t pointer
    iqueue_t *iqp = (iqueue_t*)qp;

    // Create a new element to represent the element to be added
    element_t *new_element = (element_t*)malloc(sizeof(element_t));
    if (new_element == NULL) {
        return -1; // Nonzero value for failure
    }

    // Set the val_p field to point to the provided elementp
    new_element->val_p = elementp;

    // Initialize the next field to NULL as it's the last element in the queue
    new_element->next = NULL;

    // Update the back pointer to point to the new element
    if (iqp->back == NULL) {
        // If the queue is empty, set both front and back to the new element
        iqp->front = new_element;
        iqp->back = new_element;
    } else {
        // Otherwise, update the back element's next pointer
        iqp->back->next = new_element;
        // Update the back pointer to the new element
        iqp->back = new_element;
    }

    return 0; // Zero for success
}


bool searchfn(void* elementp, const void* keyp) {
        return (*(int*)elementp == *(int*)keyp);
}

void* qsearch(queue_t *qp,  bool (*searchfn)(void* elementp,const void* keyp), const void* skeyp){

	element_t *current = qp->front;
    while (current != NULL) {
        if (searchfn(current->data, skeyp)) {
            return current->data;
        }
        current = current->next;
    }

    // Element not found
    return NULL;
	
}

void* qremove(queue_t *qp,                                                      
              bool (*searchfn)(void* elementp,const void* keyp),                
              const void* skeyp){

	if (qp == NULL || searchfn == NULL || skeyp == NULL) {
        return NULL; // Handle invalid input
    }

    // Initialize pointers to track the current and previous elements
    element_t *current = qp->front;
    element_t *prev = NULL;

    while (current != NULL) {
        // Call the search function with the current element and key
        if (searchfn(current->data, skeyp)) {
            // Element found, remove it from the queue
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                // If the first element matches, update the front pointer
                qp->front = current->next;
            }

            // If the last element matches, update the back pointer
            if (current == qp->back) {
                qp->back = prev;
            }

            // Store the element to return
            void* removedElement = current->data;

            // Free the element structure (not the data)
            free(current);

            return removedElement;
        }

        // Move to the next element
        prev = current;
        current = current->next;
    }

    // Element not found
    return NULL;
}

void qconcat(queue_t *q1p, queue_t *q2p){
	if (q1p == NULL || q2p == NULL) {
        return; // Handle invalid input
    }

    // If q2 is empty, there's nothing to concatenate
    if (q2p->front == NULL) {
        return;
    }

    // If q1 is empty, set q1's front and back pointers to q2's front and back pointers
    if (q1p->front == NULL) {
        q1p->front = q2p->front;
        q1p->back = q2p->back;
    } else {
        // If q1 is not empty, connect q1's back to q2's front
        q1p->back->next = q2p->front;
        q1p->back = q2p->back;
    }

    // Clear q2 and deallocate it
    q2p->front = NULL;
    q2p->back = NULL;
    qclose(q2p);
}


