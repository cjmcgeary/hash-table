#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#pragma once

#include <stdlib.h>

typedef struct HashTable* hashtable_t;
typedef struct HashNode* hashnode_t;

// @param: data - Pointer to a memory allocated array of hash nodes
// @param: func - Pointer to a hash function for index mapping
struct HashTable {
    size_t size;
    hashnode_t* data;
    size_t(*func)(hashtable_t hashtable, void* key);
};

// @param: key  - Pointer to a memory allocated array of hash nodes
// @param: val  - Pointer to a hash function
// @param: next - Pointer to the next node
struct HashNode {
    void* key;
    void* val;
    hashnode_t next;
};

// @desc:   Allocate memory for the hash table and designate a hash function.
// @param:  hashtable   - a pointer to the type hashtable_t
// @param:  hashsize    - the number of items to store in the hashtable
// @param:  hashfunc    - a pointer to a hashfunction that returns a hashtable index
// @return: Pointer to the allocated memory, or NULL if the request failed.
void hashtable_init(hashtable_t* hashtable, size_t size, void* hashfunc);

// @desc:   Add an item to the hash table with the specified key. If the key
//          already exists, then the value is overwritten. If the key doesn't
//          exist, then the item is inserted at the front of the linked list.
// @param:  hashtable   - a pointer to the hashtable
// @param:  key         - a pointer to the key used for index mapping
// @param:  value       - a pointer to the value associated with the key
void hashtable_set(hashtable_t hashtable, void* key, void* value);

// @desc:   Get an item from the hash table with the specified key.
// @param:  hashtable   - a pointer to the hashtable
// @param:  key         - a pointer to the key used for index mapping
// @return: Void pointer to the found value, or NULL if not found.
void* hashtable_get(hashtable_t hashtable, void* key);

// @desc:   Get an item from the hash table with the specified key and
//          remove it from the hash table.
// @param:  hashtable   - a pointer to the hashtable
// @param:  key         - a pointer to the key used for index mapping
// @return: Void pointer to the found value, or NULL if not found.
void* hashtable_pop(hashtable_t hashtable, void* key);

// @desc:   Get the size (total capacity) of the hashtable.
// @param:  hashtable   - a pointer to the hashtable
// @return: The size (total capacity) of the hashtable.
size_t hashtable_size(hashtable_t hashtable);

// @desc:   Resize the hash table to the specified size. The stored items are re-
//          mapped using the hash function supplied during initialization. There
//          must be enough memory to duplicate the hash table for this to work.
// @param:  hashtable   - a pointer to the hashtable
// @param:  hashsize    - the number of items to store in the hashtable
void hashtable_resize(hashtable_t hashtable, size_t hashsize);

#endif // !HASH_TABLE_H
