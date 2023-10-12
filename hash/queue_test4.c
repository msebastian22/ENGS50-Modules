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

bool sameName(void* elementp, const void* keyp) {                                                                            person_t* pp = (person_t*) elementp;                                                                                 
    const char* k = (char*) keyp;                                                                                            if(strcmp(pp->name, k) == 0){                                                                    
      return true;                                                                                                       
    }                                                                                                                   
    else{                                                                                                               
      return false;                                                                                                     
    }                                                                                                                    
}

int main(void) {                                                                                                  
                                                                                                                  
  hashtable_t* ht1 = hopen(50);
  hashtable_t* ht2 = hopen(50);                                   

	person_t person1 = { .name = "John", .age = 20};                                               
  person_t person2 = { .name = "James", .age = 21};                                            

	  hput(ht1, &person1, person1.name, sizeof(person1.name));                                       
    hput(ht1, &person2, person2.name, sizeof(person2.name));                                       
    
    person_t* remove = (person_t*) hremove(ht1, sameName, person1.name, sizeof(person1.name));                      
    person_t* removeSearch = (person_t*) hsearch(ht1, sameName, person1.name, sizeof(person1.name));                
    if (remove != &person1 || removeSearch != NULL) {                                                                
        printf("hremove failed when person is in table");                                                       
        exit(EXIT_FAILURE);                                                                                       
    }                                                                                                             
    printf("hremove success when person is in table");                                                           
                                                                                                                  
    person_t* removeImposter = (person_t*) hremove(ht1, sameName, "Bob", sizeof("Bob"));                           
    if (removeImposter != NULL) {                                                                                      
        printf("hremove failed when person is not in table");                                                    
        exit(EXIT_FAILURE);                                                                                       
    }                                                                                                             
    printf("hremove success when person is not in table");                                                        
                                                                                                                  
    person_t* removeNoOne = (person_t*) hremove(ht2, sameName, person1.name, sizeof(person1.name));             
    if (removeNoOne != NULL) {                                                                                    
        printf("hremove failed when table is empty");                                                             
        exit(EXIT_FAILURE);                                                                                       
    }               
    printf("hremove success when table is empty");
					 
		hclose(ht1);                                                                                                    
    hclose(ht2);
}
