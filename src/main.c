#include <stdio.h>
#include "hash_table.h"

hashtable_t hashtable;

// Create a hashtable function that index maps keys
size_t hashfunc(hashtable_t hashtable, void* key) {
    return (unsigned int) key % hashtable->size;
}

void main() {
    char* key1 = "key1";
    char* key2 = "key2";
    char* val1 = "val1";
    char* val2 = "val2";
    
    // Initialize the hashtable
    hashtable_init(&hashtable, 5, &hashfunc);
    
    if (hashtable != NULL) {
        // Add an item to the hash table
        hashtable_set(hashtable, &key1, &val1);
        // Add another item to the hash table
        hashtable_set(hashtable, &key2, &val2);
        
        // Print the size of the hash table
        size_t size = hashtable_size(hashtable);
        printf("Hash table size: %i\r\n", size);
        
        // Get the value associated with key1 from the hash table and print 
        // the returned value. hashtable_get() returns NULL if the key wasn't 
        // found, so an if-statement is used to prevent errors from occuring.
        void* value = hashtable_get(hashtable, &key1);
        if (value != NULL) {
            printf("Key: \"%s\", Value: \"%s\"\r\n", key1, *((char**)value));
        }
        
        // Print the value associated with key2
        value = hashtable_get(hashtable, &key2);
        if (value != NULL) {
            printf("Key: \"%s\", Value: \"%s\"\r\n", key2, *((char**)value));
        }

        // Change the value associated with key1
        hashtable_set(hashtable, &key1, &val2);

        // Pop the value associated with key1 from the hash table
        value = hashtable_pop(hashtable, &key1);
        if (value != NULL) {
            printf("Key: \"%s\", Value: \"%s\"\r\n", key1, *((char**)value));
        }

        // Attempt to print the value associated with key1 (spoiler: it won't print)
        value = hashtable_get(hashtable, &key1);
        if (value != NULL) {
            printf("Key: \"%s\", Value: \"%s\"\r\n", key1, *((char**)value));
        }
    }
}