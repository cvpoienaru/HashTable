/******************************************************************************
* FILE: hashtable.h
* AUTHOR: Codrin-Victor Poienaru, 334CB
* DESCRIPTION: The definition of a hashtable.
******************************************************************************/

#include "bucket.h"

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#define DOUBLE_MODE 1
#define HALVE_MODE 2
#define DOUBLE 2
#define HALVE 0.5

/*
 * Represents a hashtable.
 * A hashtable keeps track of its own size and also of a list of buckets.
 */
struct hashtable {
	struct bucket** buckets;
	unsigned int size;
};

/*
 * Allocates memory for a hashtable.
 * Returns a pointer to the allocated memory zone in case of success or a NULL
 * pointer otherwise.
 */
struct hashtable* alloc_hashtable(const int size);

/*
 * Frees the memory zone occupied by a hashtable.
 */
void free_hashtable(struct hashtable** addr);

/*
 * Adds a node to the current hashtable, containing the given information.
 * Returns a pointer to the added element if successfull or NULL otherwise.
 */
struct node* add_hashtable(
	struct hashtable* addr,
	char* info);

/*
 * Removes the node matching the specified information from the current
 * hashtable.
 * Returns a pointer to the removed element if successfull or NULL otherwise.
 */
struct node* remove_hashtable(
	struct hashtable* addr,
	char* info);

/*
 * Searches a hashtable for a particular node, matching the specified
 * information.
 * Returns a pointer to the element if found or NULL otherwise.
 */
struct node* search_hashtable(
	struct hashtable* addr,
	char* info);

/*
 * Resizes the given hashtable based on the specified resize mode: double or
 * halve. The resizing creates a hard copy of the actual hashtable, transferring
 * all the elements from the old one to the new one.
 * Returns a pointer to the new hashtable if successfull or NULL otherwise.
 */
struct hashtable* resize_hashtable(
	struct hashtable** addr,
	const int mode);

/*
 * Clears all the useful information from a hashtable.
 * This implies cleaning the buckets for any element.
 */
void clear_hashtable(struct hashtable* addr);

#endif