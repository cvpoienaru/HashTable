/******************************************************************************
* FILE: hashtable.c
* AUTHOR: Codrin-Victor Poienaru, 334CB
* DESCRIPTION: The implementation of a hashtable.
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "hashtable.h"

/*
 * Allocates memory for a hashtable.
 * Returns a pointer to the allocated memory zone in case of success or a NULL
 * pointer otherwise.
 */
struct hashtable* alloc_hashtable(const int size)
{
	struct hashtable* addr;

	addr = (struct hashtable*)malloc(sizeof(struct hashtable));
	if(!addr)
		return NULL;

	addr->buckets = (struct bucket**)calloc(size, sizeof(struct bucket));
	if(!addr->buckets) {
		free(addr);
		return NULL;
	}

	addr->size = size;
	return addr;
}

/*
 * Frees the memory zone occupied by a hashtable.
 */
void free_hashtable(struct hashtable** addr)
{
	unsigned int i;
	struct bucket* curr;

	if(!addr || !(*addr))
		return;

	/* In order to free the hashtable we must first free all the buckets. */
	for(i = 0; i < (*addr)->size; ++i) {
		curr = (*addr)->buckets[i];
		if(curr) {
			free_bucket(&curr);
			(*addr)->buckets[i] = NULL;
		}
	}

	free((*addr)->buckets);
	free(*addr);
	*addr = NULL;
}

/*
 * Gets the needed bucket based on the given information.
 * In order to obtain the desired bucket, the information is first hashed.
 */
static struct bucket* get_bucket(
	struct hashtable* addr,
	char* info)
{
	return addr->buckets[hash(info, addr->size)];
}

/*
 * Adds a node to the current hashtable, containing the given information.
 * Returns a pointer to the added element if successfull or NULL otherwise.
 */
struct node* add_hashtable(
	struct hashtable* addr,
	char* info)
{
	return add_bucket(&addr->buckets[hash(info, addr->size)], info);
}

/*
 * Removes the node matching the specified information from the current
 * hashtable.
 * Returns a pointer to the removed element if successfull or NULL otherwise.
 */
struct node* remove_hashtable(
	struct hashtable* addr,
	char* info)
{
	return remove_bucket(&addr->buckets[hash(info, addr->size)], info);
}

/*
 * Searches a hashtable for a particular node, matching the specified
 * information.
 * Returns a pointer to the element if found or NULL otherwise.
 */
struct node* search_hashtable(
	struct hashtable* addr,
	char* info)
{
	return search_bucket(get_bucket(addr, info), info);
}

/*
 * Resizes the given hashtable based on the specified resize mode: double or
 * halve. The resizing creates a hard copy of the actual hashtable, transferring
 * all the elements from the old one to the new one.
 * Returns a pointer to the new hashtable if successfull or NULL otherwise.
 */
struct hashtable* resize_hashtable(
	struct hashtable** addr,
	const int mode)
{
	unsigned int i;
	struct hashtable* new_hashtable = NULL;
	struct node* curr;

	switch(mode) {
		case DOUBLE_MODE:
			new_hashtable = alloc_hashtable(DOUBLE * (*addr)->size);
			if(!new_hashtable) {
				goto exit;
			}
			break;

		case HALVE_MODE:
			if((*addr)->size % 2 == 0) {
				new_hashtable = alloc_hashtable(
					(int)(HALVE * ((double)(*addr)->size)));
			} else {
				new_hashtable = alloc_hashtable(
					(int)(HALVE * ((double)(*addr)->size - 1)));
			}

			if(!new_hashtable) {
				goto exit;
			}
			break;
	}

	/*
	 * For each bucket, remove the contained nodes and transfer them to the
	 * new hashtable.
	 */
	for(i = 0; i < (*addr)->size; ++i) {
		while(1) {
			if(!(*addr)->buckets[i] || !(*addr)->buckets[i]->start)
				break;

			curr = remove_bucket(
				&(*addr)->buckets[i],
				(*addr)->buckets[i]->start->info);
			add_hashtable(new_hashtable, strdup(curr->info));
			free_node(&curr);
		}
	}

	/* Free the old hashtable. */
	free_hashtable(addr);

exit:
	return new_hashtable;
}

/*
 * Clears all the useful information from a hashtable.
 * This implies cleaning the buckets for any element.
 */
void clear_hashtable(struct hashtable* addr)
{
	unsigned int i;
	struct bucket* curr;

	/* Clearing a hashtable means freeing all the buckets. */
	for(i = 0; i < addr->size; ++i) {
		curr = addr->buckets[i];
		if(curr) {
			free_bucket(&curr);
			addr->buckets[i] = NULL;
		}
	}
}