/******************************************************************************
* FILE: list.c
* AUTHOR: Codrin-Victor Poienaru, 334CB
* DESCRIPTION: The implementation of a double linked list.
******************************************************************************/

#include <stdlib.h>
#include "list.h"

/*
 * Allocates memory for a node.
 * Returns a pointer to the allocated memory zone in case of success or a NULL
 * pointer otherwise.
 */
struct node* alloc_node(void* info)
{
	struct node* addr;

	addr = (struct node*)malloc(sizeof(struct node));
	if(!addr)
		return NULL;

	if(!info) {
		addr->info = malloc(sizeof(info));
		if(!addr->info) {
			free(addr);
			return NULL;
		}
	} else {
		addr->info = info;
	}

	addr->next = NULL;
	addr->prev = NULL;
	return addr;
}

/*
 * Frees the memory zone occupied by a node.
 */
void free_node(struct node** addr)
{
	if(!addr || !(*addr))
		return;

	if((*addr)->info)
		free((*addr)->info);
	free(*addr);
	*addr = NULL;
}

/*
 * Searches a double linked list for a particular node, matching the specified
 * information, starting from the given node and using the specified comparer.
 * Returns a pointer to the element if found or NULL otherwise.
 */
struct node* search_node(
	struct node* addr,
	void* info,
	int (*compare)(void* info1, void* info2))
{
	struct node* p;

	for(p = addr; p; p = p->next)
		if(compare(p->info, info) == 0)
			return p;

	return NULL;
}

/*
 * Adds a node to a double linked list after the specified node and containing
 * the given information.
 * Returns a pointer to the added element if successfull or NULL otherwise.
 */
struct node* add_last_node(
	struct node** addr,
	void* info)
{
	struct node* curr;

	if(!addr || !(*addr)) {
		*addr = alloc_node(info);
		if(!(*addr))
			return NULL;

		return *addr;
	}

	curr = alloc_node(info);
	if(!curr)
		return NULL;

	(*addr)->next = curr;
	curr->prev = *addr;
	return curr;
}

/*
 * Removes the given node from a double linked list.
 * Returns a pointer to the removed element if successfull or NULL otherwise.
 */
struct node* remove_node(struct node** addr)
{
	struct node* curr;

	if(!addr || !(*addr))
		return NULL;

	curr = *addr;
	if(!curr->prev) {
		*addr = curr->next;
		if(curr->next)
			curr->next->prev = NULL;
	} else if(!curr->next) {
		curr->prev->next = NULL;
	} else {
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
	}

	return curr;
}