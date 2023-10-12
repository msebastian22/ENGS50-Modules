/* 
 * hash.c -- implements a generic hash table as an indexed set of queues.
 *
 */
#include "hash.h"
#include "queue.c"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/* 
 * SuperFastHash() -- produces a number between 0 and the tablesize-1.
 * 
 * The following (rather complicated) code, has been taken from Paul
 * Hsieh's website under the terms of the BSD license. It's a hash
 * function used all over the place nowadays, including Google Sparse
 * Hash.
 */
#define get16bits(d) (*((const uint16_t *) (d)))

static uint32_t SuperFastHash (const char *data,int len,uint32_t tablesize) {
  uint32_t hash = len, tmp;
  int rem;
  
  if (len <= 0 || data == NULL)
		return 0;
  rem = len & 3;
  len >>= 2;
  /* Main loop */
  for (;len > 0; len--) {
    hash  += get16bits (data);
    tmp    = (get16bits (data+2) << 11) ^ hash;
    hash   = (hash << 16) ^ tmp;
    data  += 2*sizeof (uint16_t);
    hash  += hash >> 11;
  }
  /* Handle end cases */
  switch (rem) {
  case 3: hash += get16bits (data);
    hash ^= hash << 16;
    hash ^= data[sizeof (uint16_t)] << 18;
    hash += hash >> 11;
    break;
  case 2: hash += get16bits (data);
    hash ^= hash << 11;
    hash += hash >> 17;
    break;
  case 1: hash += *data;
    hash ^= hash << 10;
    hash += hash >> 1;
  }
  /* Force "avalanching" of final 127 bits */
  hash ^= hash << 3;
  hash += hash >> 5;
  hash ^= hash << 4;
  hash += hash >> 17;
  hash ^= hash << 25;
  hash += hash >> 6;
  return hash % tablesize;
}

typedef struct hashtable {
	uint32_t size;
	queue_t **table;
} hashTable_t;

hashtable_t *hopen(uint32_t hsize){
// Initialize the size and allocate memory for the table
	hashTable_t *ht = (hashTable_t *)malloc(sizeof(hashTable_t));
    if (ht == NULL) {
        perror("Error: Unable to allocate memory for the hash table.");
        return NULL;
    }

     
		ht->table = (queue_t **)calloc((size_t) hsize, sizeof(queue_t **));;
    ht->size = hsize;
		

    return ht;
}

void hclose(hashtable_t *htp){
	if (htp == NULL) {
        return;
    }
	hashTable_t *ht = htp;
	for (uint32_t i = 0; i < (ht->size); i++) {
		if((ht->table[i]) != NULL){
			qclose((ht->table[i]));
        }
			
    }

    free(ht->table);
    free(ht);
}

int32_t hput(hashtable_t *htp, void *ep, const char *key, int keylen){
	
	if (htp == NULL || ep == NULL || key == NULL || keylen <= 0) {
        return -1;  // Invalid input
    }
	hashTable_t *ht = htp;
	uint32_t index = SuperFastHash(key, keylen, ht->size); // Implement a suitable hash function here
	
	if((ht->table)[index] == NULL){
		queue_t * qp = qopen();
		qput(qp, ep);
		(ht->table)[index] = qp;
		return 0;
	}
	else{
		queue_t *qp = (ht->table)[index];
		qput(qp, ep);
		return 0;
	}
    
    return -1;  // Failure
}


void happly(hashtable_t *htp, void (*fn)(void* ep)) {
    if (htp == NULL) {
        return;
    }
		hashTable_t *ht = htp;

    for (uint32_t i = 0; i < (ht->size); i++) {
			queue_t *qp = (ht->table)[i];
			if(qp != NULL){
				qapply(qp, fn);
			}
    }
}

void *hsearch(hashtable_t *htp, bool (*searchfn)(void* elementp, const void* searchkeyp),const char *key,int32_t keylen){
	if (htp == NULL || searchfn == NULL || key == NULL) {
        return NULL;
    }
	hashTable_t *ht = htp;
	uint32_t index = SuperFastHash(key, keylen, ht->size);
	queue_t *qp = (ht->table)[index];
	void *isThere = qsearch(qp, searchfn, key);
	return isThere;
		
  
}

void *hremove(hashtable_t *htp,                                                 
							bool (*searchfn)(void* elementp, const void* searchkeyp),               
							const char *key,                                                        
							int32_t keylen){
	if (htp == NULL || searchfn == NULL || key == NULL) {
		return NULL;
	}
	hashTable_t *ht = htp;
	uint32_t index = SuperFastHash(key, keylen, ht->size);
	queue_t *qp = (ht->table)[index];
	void *removed = qremove(qp, searchfn, key);
	return removed;

	

}
