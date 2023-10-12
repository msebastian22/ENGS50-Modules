/* 
 * queue_test1.c --- 
 * 
 * Author: Matthew J. Sebastian
 * Created: 10-12-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include <string.h>

typedef struct person {                                                                                              
  char name[50];                                                                                             
  double age;                                                                                                            
} person_t;                                                                                                          
 
int main(void) {                                                                                                  
                                                                                                                  
  hashtable_t* ht1 = hopen(50);

	person_t person1 = { .name = "John", .age = 20};                                               
  person_t person2 = { .name = "James", .age = 21};                                            
  

	  int32_t r1 = hput(ht1, &person1, person1.name, sizeof(person1.name));                                       
    if (r1 != 0) {                                                                                           
      printf("hput on empty table failed");
      exit(EXIT_FAILURE);                                                                                         
    }                                                                                                             
    printf("hput on empty table success");
                                                                                                                  
  int32_t r2 = hput(ht1, &person2, person2.name, sizeof(person2.name));                                       
    if (r2 != 0) {                                                                                           
      printf("hput on non-empty table failed");
      exit(EXIT_FAILURE);                                                                                         
    }                                                                                                             
    printf("hput on non-empty table success");

		hclose(ht1);
}
