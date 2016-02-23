#include "hash.h"

/*
 * Hash function based on Dan Bernstein's djb2.
 * http://www.cse.yorku.ca/~oz/hash.html
 * @return dispersion code (the key)
 */
unsigned int hash(const char *str, unsigned int hash_length)
{
	unsigned int hash = 5381;
	int c;

	while ((c = *str++) != 0)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return (hash % hash_length);
}