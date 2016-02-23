#ifndef HASH_H_
#define HASH_H_

/*
 * Hash function based on Dan Bernstein's djb2.
 * http://www.cse.yorku.ca/~oz/hash.html
 * @return dispersion code (the key)
 */
unsigned int hash(const char *str, unsigned int hash_length);

#endif