/* 
 * queue_test1.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-10-2023
 * Version: 1.0
 * 
 * Description:  to successfully open a queue, add an element , close the queue
 * 
 */

#include <math.h>                                                                                         
#include "queue.h"                                                                                         
#include <stdio.h>                                                                                        
#include <stdint.h>                                                                                       
#include <stdlib.h>                                                                                       
#include <string.h>

typedef struct car {                                                                            
  int year;
} car_t;

int main(){
	queue_t *myQueue = qopen();

	//assign cars as data
	//then put data into queue
	car_t *newCar = malloc(sizeof(car_t));
	newCar->year = 5;
	car_t *newCar2 = malloc(sizeof(car_t));
	newCar2->year = 1;
	car_t *newCar3 = malloc(sizeof(car_t));
	newCar3-> year = 3;

	
	qput(myQueue,newCar);
	qput(myQueue,newCar2);
	qput(myQueue,newCar3);

	if (qput(myQueue, newCar) != 0 ||
			qput(myQueue, newCar2) != 0 ||
			qput(myQueue, newCar3) != 0) {
        qclose(myQueue);
        exit(EXIT_FAILURE);
    }

		qclose(myQueue);
		exit(EXIT_SUCCESS);
}
