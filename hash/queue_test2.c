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

void doubleAge(void* ep) {                                                                                              
    person_t* pp = (person_t*) ep;                                                                                      
    pp->age *= 2;                                                                                                       
}                

int main(void) {                                                                                                  
                                                                                                                  
  hashtable_t* ht1 = hopen(50);
  hashtable_t* ht2 = hopen(50);                                   

	person_t person1 = { .name = "John", .age = 20};                                               
  person_t person2 = { .name = "James", .age = 21};                                            
  person_t person1Copy = { .name = "John", .age = 20};                                               
  person_t person2Copy = { .name = "James", .age = 21};  

	  hput(ht1, &person1, person1.name, sizeof(person1.name));                                       
    hput(ht1, &person2, person2.name, sizeof(person2.name));                                       
    
    happly(ht1, doubleAge);                                                                               
    if (person1.age != person1Copy.age * 2 ||person2.age != person2Copy.age * 2){                                        
        printf("happly on non-empty table failed");                                                  
        exit(EXIT_FAILURE);                                                                                       
    }                                                                                                             
    printf("happly on non-empty table success");                                                      
                                                                                                                  
    happly(ht2, doubleAge);                                                                              
    printf("happly on empty table success");


		hclose(ht1);                                                                                                    
    hclose(ht2);
}
