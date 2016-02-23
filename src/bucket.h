/******************************************************************************
* FILE: bucket.h
* AUTHOR: Codrin-Victor Poienaru, 334CB
* DESCRIPTION: The definition of a bucket.
******************************************************************************/

#include <stdio.h>
#include "list.h"

#ifndef BUCKET_H_
#define BUCKET_H_

/*
 * Represents a hashtable bucket.
 * A bucket keeps track of the start and the end of a double linked list used
 * for storing bucket elements.
 */
struct bucket {
	struct node* start;
	struct node* end;
};

/*
 * Allocates memory for a bucket.
 * Returns a pointer to the allocated memory zone in case of success or a NULL
 * pointer otherwise.
 */
struct bucket* alloc_bucket(char* info);

/*
 * Frees the memory zone occupied by a bucket.
 */
void free_bucket(struct bucket** addr);

/*
 * Searches a bucket for a particular node, matching the specified information.
 * Returns a pointer to the element if found or NULL otherwise.
 */
struct node* search_bucket(
	struct bucket* addr,
	char* info);

/*
 * Adds a node to the end of a bucket, containing the given information.
 * Returns a pointer to the added element if successfull or NULL otherwise.
 */
struct node* add_bucket(
	struct bucket** addr,
	char* info);

/*
 * Removes the node matching the specified information from the current bucket.
 * Returns a pointer to the removed element if successfull or NULL otherwise.
 */
struct node* remove_bucket(
	struct bucket** addr,
	char* info);

/*
 * Prints the contents of the given bucket to the specified output file.
 */
void print_bucket(
	struct bucket* addr,
	FILE* fout);

#endif