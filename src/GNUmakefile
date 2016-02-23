CC = gcc
CFLAGS = -Wall -O3 -O2 -g

build: hashtable

hashtable: main.o hash.o list.o bucket.o hashtable.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c
hash.o: hash.h hash.c
list.o: list.h list.c
bucket.o: bucket.h bucket.c
hashtable.o: hashtable.h hashtable.c

.PHONY: clean
clean:
	rm -rf *.o hashtable
