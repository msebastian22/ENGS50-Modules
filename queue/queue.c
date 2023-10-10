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

typedef void{                                                           
  element_t *front;
	element_t *back;                                                         
} queue_t;



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
