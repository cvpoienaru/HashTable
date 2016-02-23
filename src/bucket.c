/******************************************************************************
* FILE: bucket.c
* AUTHOR: Codrin-Victor Poienaru, 334CB
* DESCRIPTION: The implementation of a bucket.
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bucket.h"

/*
 * Compares two strings returning their relative order.
 */
static int compare_strings(void* str1, void* str2)
{
	return strcmp((char*)str1, (char*)str2);
}

/*
 * Allocates memory for a bucket.
 * Returns a pointer to the allocated memory zone in case of success or a NULL
 * pointer otherwise.
 */
struct bucket* alloc_bucket(char* info)
{
	struct bucket* addr;

	addr = (struct bucket*)malloc(sizeof(struct bucket));
	if(!addr)
		return NULL;

	addr->start = NULL;
	addr->end = NULL;

	addr->start = add_last_node(&addr->start, info);
	if(!addr->start) {
		free(addr);
		return NULL;
	}

	addr->end = addr->start;
	return addr;
}

/*
 * Frees the memory zone occupied by a bucket.
 */
void free_bucket(struct bucket** addr)
{
	struct node* p;
	struct node* curr;

	if(!addr || !(*addr))
		return;

	/* Free all the elements contained in the bucket. */
	p = (*addr)->start;
	while(p) {
		curr = p;
		p = p->next;
		free_node(&curr);
	}

	(*addr)->start = NULL;
	(*addr)->end = NULL;
	free(*addr);
	*addr = NULL;
}

/*
 * Searches a bucket for a particular node, matching the specified information.
 * Returns a pointer to the element if found or NULL otherwise.
 */
struct node* search_bucket(
	struct bucket* addr,
	char* info)
{
	if(!addr)
		return NULL;

	return search_node(addr->start, info, compare_strings);
}

/*
 * Adds a node to the end of a bucket, containing the given information.
 * Returns a pointer to the added element if successfull or NULL otherwise.
 */
struct node* add_bucket(
	struct bucket** addr,
	char* info)
{
	struct node *found, *curr;

	if(!addr || !(*addr)) {
		*addr = alloc_bucket(info);
		if(!addr || !(*addr))
			return NULL;

		return (*addr)->start;
	}

	/* Don't allow duplicates. */
	found = search_bucket(*addr, info);
	if(found)
		return NULL;

	curr = add_last_node(&((*addr)->end), info);
	if(!curr) {
		free_bucket(addr);
		return NULL;
	}

	if(!(*addr)->start) {
		(*addr)->start = curr;
	}

	(*addr)->end = curr;
	return curr;
}

/*
 * Removes the node matching the specified information from the current bucket.
 * Returns a pointer to the removed element if successfull or NULL otherwise.
 */
struct node* remove_bucket(
	struct bucket** addr,
	char* info)
{
	struct node *found, *curr;

	if(!addr || !(*addr))
		return NULL;

	/* Cannot remove an non-existing element. */
	found = search_bucket(*addr, info);
	if(!found)
		return NULL;

	curr = remove_node(&found);
	if(!curr->prev && !curr->next) {
		(*addr)->start = curr->next;
		(*addr)->end = curr->prev;
	}
	else if(!curr->prev)
		(*addr)->start = curr->next;
	else if(!curr->next)
		(*addr)->end = curr->prev;

	return curr;
}

/*
 * Prints the contents of the given bucket to the specified output file.
 */
void print_bucket(
	struct bucket* addr,
	FILE* fout)
{
	struct node* p;

	if(!addr)
		return;

	for(p = addr->start; p; p = p->next)
		fprintf(fout, "%s ", (char*)p->info);
	fprintf(fout, "\n");
}