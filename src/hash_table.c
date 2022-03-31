#include "hash_table.h"

// Forward declaration of the private functions
static size_t hashtable_index(hashtable_t hashtable, void* key);
static hashnode_t hashnode_get(hashtable_t hashtable, void* key);
static hashnode_t hashnode_create(void* key, void* val, hashnode_t next);

// @desc:   Allocate memory for the hash table and designate a hash function.
// @param:  hashtable   - a pointer to the type hashtable_t
// @param:  hashsize    - the number of items to store in the hashtable
// @param:  hashfunc    - a pointer to a hashfunction that returns a hashtable index
// @return: Pointer to the allocated memory, or NULL if the request failed.
void hashtable_init(hashtable_t* hashtable, size_t hashsize, void* hashfunc) {
    (*hashtable) = (hashtable_t) malloc(sizeof(struct HashTable));
    if (*hashtable != NULL) {
        (*hashtable)->size = hashsize;
        (*hashtable)->data = (hashnode_t*) calloc(hashsize, sizeof(hashnode_t));
        (*hashtable)->func = hashfunc;
    }
}

// @desc:   Add an item to the hash table with the specified key. If the key
//          already exists, then the value is overwritten. If the key doesn't
//          exist, then the item is inserted at the end of the linked list.
// @param:  hashtable   - a pointer to the hashtable
// @param:  key         - a pointer to the key used for index mapping
// @param:  value       - a pointer to the value associated with the key
void hashtable_set(hashtable_t hashtable, void* key, void* val) {
    hashnode_t node = hashnode_get(hashtable, key);

    // Key found, so overwrite the value
    if (node != NULL) {
        node->val = val;
    }
    // Key not found, so insert the new item
    else {
        node = hashnode_create(key, val, NULL);

        if (node != NULL) {
            // Get the head node
            size_t index = hashtable_index(hashtable, key);
            hashnode_t head = (hashnode_t) ((char*)(hashtable->data)[index]);

            // Head node present, so set next as the head node
            if (head != NULL) {
                node->next = head;
            }

            ((char*)(hashtable->data)[index]) = node;
        }
    }
}

// @desc:   Get an item from the hash table with the specified key.
// @param:  hashtable   - a pointer to the hashtable
// @param:  key         - a pointer to the key used for index mapping
// @return: Void pointer to the found value, or NULL if not found.
void* hashtable_get(hashtable_t hashtable, void* key) {
    size_t index = hashtable_index(hashtable, key);
    hashnode_t node = (hashnode_t) ((char*)(hashtable->data)[index]);
    
    while (node != NULL) {
        if (node->key == key) {
            return node->val;
        }
        node = node->next;
    }
    return NULL;
}

// @desc:   Get an item from the hash table with the specified key and
//          remove it from the hash table.
// @param:  hashtable   - a pointer to the hashtable
// @param:  key         - a pointer to the key used for index mapping
// @return: Void pointer to the found value, or NULL if not found.
void* hashtable_pop(hashtable_t hashtable, void* key) {
    // Get the head node
    size_t index = hashtable_index(hashtable, key);
    hashnode_t head = (hashnode_t)((char*)(hashtable->data)[index]);

    // Keep track of the previous and current node
    hashnode_t node = head;
    hashnode_t prev = node;

    while (node != NULL) {
        if (node->key == key) {
            void* value = node->val;

            // If the node is head, then free the memory 
            // and update the hash table pointer to NULL
            if (node == head) {
                free(head);
                (char*)(hashtable->data)[index] = NULL;
            }
            else {
                // If the node is last in the linked list, free the 
                // memory and update the previous next pointer to NULL
                if (node->next == NULL) {
                    free((void*) node);
                    prev->next = NULL;
                }
                // If the node is between two nodes, then copy the contents of 
                // the next node into the current node and free next's memory
                else {
                    node->key = node->next->key;
                    node->val = node->next->val;
                    node->next = node->next->next;
                    free((void*) node->next);
                }
            }

            return value;
        }
        prev = node;
        node = node->next;
    }
    return NULL;
}

// @desc:   Get the size (total capacity) of the hashtable.
// @param:  hashtable   - a pointer to the hashtable
// @return: The size (total capacity) of the hashtable.
size_t hashtable_size(hashtable_t hashtable) {
    return hashtable->size;
}

// @desc:   Resize the hash table to the specified size. The stored items are re-
//          mapped using the hash function supplied during initialization. There
//          must be enough memory to duplicate the hash table for this to work.
// @param:  hashtable   - a pointer to the hashtable
// @param:  hashsize    - the number of items to store in the hashtable
void hashtable_resize(hashtable_t hashtable, size_t hashsize) {
    // @TODO: Add code to resize the hash table
}

// @desc:   Map an item to an index in the hash table. The function is static
//          and therefore restricts access to this file only.
// @param:  hashtable   - a pointer to the hashtable
// @param:  key         - a pointer to the key used for index mapping
static size_t hashtable_index(hashtable_t hashtable, void* key) {
    return (*hashtable->func)(hashtable, key);
}

// @desc:   Get a node from the hash table with the specified key. The function
//          is static and therefore restricts access to this file only.
// @param:  hashtable   - a pointer to the hashtable
// @param:  key         - a pointer to the key used for index mapping
// @return: Pointer to the found node, or NULL if not found.
static hashnode_t hashnode_get(hashtable_t hashtable, void* key) {
    size_t index = hashtable_index(hashtable, key);
    hashnode_t node = (hashnode_t)((char*)(hashtable->data)[index]);

    while (node != NULL) {
        if (node->key == key) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

// @desc:   Create a new hashtable node. The function is static and therefore
//          restricts access to this file only.
// @param:  key     - a pointer to the key used for index mapping
// @param:  val     - a pointer to the value associated with the key
// @param:  next    - a pointer to the next node
// @return: Pointer to the allocated memory, or NULL if the request failed.
static hashnode_t hashnode_create(void* key, void* val, hashnode_t next) {
    hashnode_t node = (hashnode_t) malloc(sizeof(struct HashNode));
    if (node != NULL) {
        node->key = key;
        node->val = val;
        node->next = next;
    }
    return node;
}