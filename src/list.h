/******************************************************************************
* FILE: list.h
* AUTHOR: Codrin-Victor Poienaru, 334CB
* DESCRIPTION: The definition of a double linked list.
******************************************************************************/

#ifndef LIST_H_
#define LIST_H_

/*
 * Represents a double linked list node.
 */
struct node {
	void* info;
	struct node* next;
	struct node* prev;
};

/*
 * Allocates memory for a node.
 * Returns a pointer to the allocated memory zone in case of success or a NULL
 * pointer otherwise.
 */
struct node* alloc_node(void* info);

/*
 * Frees the memory zone occupied by a node.
 */
void free_node(struct node** addr);

/*
 * Searches a double linked list for a particular node, matching the specified
 * information, starting from the given node and using the specified comparer.
 * Returns a pointer to the element if found or NULL otherwise.
 */
struct node* search_node(
	struct node* addr,
	void* info,
	int (*compare)(void* info1, void* info2));

/*
 * Adds a node to a double linked list after the specified node and containing
 * the given information.
 * Returns a pointer to the added element if successfull or NULL otherwise.
 */
struct node* add_last_node(
	struct node** addr,
	void* info);

/*
 * Removes the given node from a double linked list.
 * Returns a pointer to the removed element if successfull or NULL otherwise.
 */
struct node* remove_node(struct node** addr);

#endif