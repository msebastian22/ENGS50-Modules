/* 
 * hash.c -- implements a generic hash table as an indexed set of queues.
 *
 */
#include <stdint.h>
#include "hash.h"
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

hashtable_t *hopen(uint32_t hsize){
	hashtable_t *ht = (hashtable_t *)malloc(sizeof(hashtable_t));
    if (ht == NULL) {
        perror("Error: Unable to allocate memory for the hash table.");
        return NULL;
    }

    // Initialize the size and allocate memory for the table
    ht->size = hsize;
    ht->table = (struct KeyValue **)malloc(hsize * sizeof(struct KeyValue *));
    if (ht->table == NULL) {
        perror("Error: Unable to allocate memory for the hash table array.");
        free(ht);
        return NULL;
    }

    // Initialize the table with NULL pointers
    for (uint32_t i = 0; i < hsize; i++) {
        ht->table[i] = NULL;
    }

    return ht;
}

void hclose(hashtable_t *htp){
	if (ht == NULL) {
        return;
    }

    for (uint32_t i = 0; i < ht->size; i++) {
        struct KeyValue *current = ht->table[i];
        while (current != NULL) {
            struct KeyValue *temp = current;
            current = current->next;
            free((void *)temp->key);
            free(temp);
        }
    }

    free(ht->table);
    free(ht);
}

int32_t hput(hashtable_t *htp, void *ep, const char *key, int keylen){
	if (ht == NULL || ep == NULL || key == NULL || keylen <= 0) {
        return -1;  // Invalid input
    }

    uint32_t index = hash_function(key) % ht->size; // Implement a suitable hash function here

    // Create a new key-value pair
    struct KeyValue *new_pair = create_pair(key, keylen, ep);
    if (new_pair == NULL) {
        return -2;  // Memory allocation error
    }

    if (ht->table[index] == NULL) {
        // If the slot is empty, insert the pair
        ht->table[index] = new_pair;
    } else {
        // If the slot is not empty, handle collisions by chaining
        struct KeyValue *current = ht->table[index];
        while (current != NULL) {
            if (strcmp(current->key, key) == 0 && current->keylen == keylen) {
                // Key already exists in the hash table; update the value
                current->value = ep;
                free((void *)key); // Free the duplicate key
                free(new_pair);    // Free the duplicate key-value pair
                return 1; // Key already exists, value updated
            }
            current = current->next;
        }
        current = new_pair; // Add the new key-value pair to the end of the chain
    }

    return 0;  // Success
}


void happly(hashtable_t *htp, void (*fn)(void* ep)) {
    if (htp == NULL) {
        return;
    }

    for (uint32_t i = 0; i < htp->size; i++) {
        struct KeyValue *current = htp->table[i];
        while (current != NULL) {
            // Apply the user-defined function to the current key-value pair
            fn(current);
            current = current->next;
        }
    }
}

void *hsearch(hashtable_t *htp, bool (*searchfn)(void* elementp, const void* searchkeyp),const char *key,int32_t keylen){
	if (htp == NULL || searchfn == NULL || key == NULL) {
        return NULL;
    }

    for (uint32_t i = 0; i < htp->size; i++) {
        struct KeyValue *current = htp->table[i];
        while (current != NULL) {
					if (searchfn(current, key, keylen)) {
							return current; // Entry found, return a pointer to the entry
            }
            current = current->next;
        }
    }
		
    return NULL; // Entry not found
}

void *hremove(hashtable_t *htp,                                                 
							bool (*searchfn)(void* elementp, const void* searchkeyp),               
							const char *key,                                                        
							int32_t keylen){
	if (ht == NULL || searchfn == NULL || key == NULL) {
		return NULL;
	}
	
	uint32_t index = hash_function(key) % ht->size; // Implement a suitable hash function here
	
	struct KeyValue *prev = NULL;
	struct KeyValue *current = ht->table[index];
	
	while (current != NULL) {
		if (searchfn(current, key, keylen)) {
			// Entry found, remove it from the hash table
			if (prev == NULL) {
				ht->table[index] = current->next;
			} else {
				prev->next = current->next;
			}
			return current; // Return a pointer to the removed entry
			}
		prev = current;
		current = current->next;
	}
	
	return NULL; // Entry not found
}
