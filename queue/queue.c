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

typedef struct element{
	void data;
	struct *element next;
} element_t;

typedef void queue_t{                                                          
  element_t *front;
	element_t *back;                                                         
};



queue_t* open(void){
	queue_t* newQueue = (queue_t*)malloc(sizeof(queue_t));
    
    if (newQueue == NULL) {
        // Handle memory allocation error if needed
        //perror("Memory allocation error");
        return NULL;
    }

    // Initialize front and back pointers to NULL
    newQueue->front = NULL;
    newQueue->back = NULL;

    return newQueue;
}

void qclose(queue_t* qp){
	if(qp == NULL){
		return;
	}

	while (qp->front != NULL) {
        // Remove and free the front node until the queue is empty
        node_t* temp = qp->front;
        qp->front = qp->front->next;
        free(temp);
    }

    // Free the queue structure itself
    free(qp);
}

int32_t qput(queue_t *qp, void *elementp){
    // Create a new node
    queue_t* newQueue = (queue_t*)malloc(sizeof(queue_t));

    if (newQueue == NULL) {
        // Handle memory allocation error
        //perror("Memory allocation error");
        return -1; // Nonzero value for failure
    }

    newQueue->data = elementp;
    newQueue->next = NULL;

    if (qp->back == NULL) {
        // If the queue is empty, set front and back to the new node
        qp->front = newQueue;
        qp->back = newQueue;
    } else {
        // Otherwise, update the back pointer and link nodes
        qp->back->next = newQueue;
        qp->back = newQueue;
    }

    return 0; // Return 0 for success
}

<<<<<<< HEAD
bool searchfn(void* elementp, const void* keyp) {
        // Implement your search logic here
        // Return TRUE if the element matches the key, otherwise return FALSE
        // You can access skeyp directly here
        return (*(int*)elementp == *(int*)keyp);
}

void* qsearch(queue_t *qp,  bool (*searchfn)(void* elementp,const void* keyp), const void* skeyp){

	element_t *current = qp->front;
    while (current != NULL) {
        // Call the search function with the current element and key
        if (searchfn(current->data, skeyp)) {
            // If the search function returns TRUE, return the element
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
=======
void* qget(queue_t *qp){
	//check queue isn't null
	if(qp == NULL){
		return NULL;
	}

	frontOrig = qp->front;
	//Check if the queue is empty, if yes then return null
	if(frontOrig == NULL){
		return NULL;
	}
	//If the list isn'r empty return the first element and remove it from the queue
	else{
		void *firstElement = frontOrig;;
		qp->front = frontOrig->next;
		frontOrig->next = NULL;
		//check if firstElement was the last element in the list
		if(qp->front == NULL){
			qp->back = NULL;
		}
		return firstElement;
	}
>>>>>>> f25042e (Adding get function)
}
