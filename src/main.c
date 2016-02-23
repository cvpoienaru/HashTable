/******************************************************************************
* FILE: main.c
* AUTHOR: Codrin-Victor Poienaru, 334CB
* DESCRIPTION: The implementation of a hashtable tool.
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "hashtable.h"

#define BUFFER_SIZE 20000
#define COMMAND_SIZE 3

#define ADD "add"
#define REMOVE "remove"
#define FIND "find"
#define CLEAR "clear"
#define PRINT_B "print_bucket"
#define PRINT "print"
#define RESIZE "resize"

#define RESIZE_DOUBLE "double"
#define TRUE "True"
#define FALSE "False"

int main(int argc, char** argv)
{
	int k, files_no, result;
	unsigned int i, j, index;
	char buffer[BUFFER_SIZE], tokens[] = " \n";
	char *command[COMMAND_SIZE];
	char *tmp, *word;
	struct node* curr_node;
	struct hashtable* main_hashtable = NULL;
	FILE* fout = NULL;

	/* Check the command line arguments. */
	if(argc < 2) {
		perror("Usage: %s <size> [<input_file1>] [<input_file2>] ...\n");
		result = EXIT_FAILURE;
		goto exit;
	}

	/* Check the size to be a valid number. */
	for(i = 0; i < strlen(argv[1]); ++i) {
		if(!isdigit(argv[1][i])) {
			perror("Error: Size is not a number.\n");
			result = EXIT_FAILURE;
			goto exit;
		}
	}

	/* Allocate memory for the hashtable to be used. */
	main_hashtable = alloc_hashtable(atoi(argv[1]));
	if(!main_hashtable) {
		perror("Error: Could not alloc hashtable.\n");
		result = EXIT_FAILURE;
		goto exit;
	}

	files_no = 0;
	while(1) {
		/* Redirect the input for each file, if necessary. */
		if(argc > 2) {
			if(files_no + 2 == argc)
				break;

			if(!freopen(argv[files_no + 2], "r", stdin)) {
				perror("Error: Could not redirect input file.\n");
				result = EXIT_FAILURE;
				goto exit;
			}
			++files_no;
		}

		/* Read a command. */
		while(fgets(buffer, BUFFER_SIZE, stdin)) {
			if(strcmp(buffer, "\n") == 0)
				continue;

			k = -1;
			command[0] = NULL;
			command[1] = NULL;
			command[2] = NULL;

			/* Split the command. */
			tmp = strtok(buffer, tokens);
			command[++k] = tmp;
			while((tmp = strtok(NULL, tokens)))
				command[++k] = tmp;

			/* Open output file if necessary. */
			result = strcmp(command[0], PRINT);
			if(k == 2 || (result == 0 && k == 1)) {
				fout = fopen((k == 2 ? command[2] : command[1]), "a");
				if(!fout) {
					perror("Error: Could not open output file.\n");
					result = EXIT_FAILURE;
					goto exit;
				}
			} else {
				fout = stdout;
			}

			if(strcmp(command[0], ADD) == 0) {
				/* Add an element to the hashtable. */
				if(!command[1])
					continue;

				word = strdup(command[1]);
				curr_node = add_hashtable(main_hashtable, word);
				if(!curr_node)
					free(word);
			} else if(strcmp(command[0], REMOVE) == 0) {
				/* Remove an element from the hashtable. */
				if(!command[1])
					continue;

				curr_node = remove_hashtable(main_hashtable, command[1]);
				free_node(&curr_node);
			} else if(strcmp(command[0], FIND) == 0) {
				/* Search an element in the hashtable. */
				if(!command[1])
					continue;

				curr_node = search_hashtable(main_hashtable, command[1]);
				fprintf(fout, "%s\n", curr_node ? TRUE : FALSE);
			} else if(strcmp(command[0], CLEAR) == 0) {
				/* Clear the hashtable. */
				clear_hashtable(main_hashtable);
			} else if(strcmp(command[0], PRINT_B) == 0) {
				/* Print the specified hashtable bucket. */
				/* Check the index to be a valid number. */
				for(j = 0; j < strlen(command[1]); ++j) {
					if(!isdigit(command[1][j])) {
						perror("Error: Index is not a number.\n");
						result = EXIT_FAILURE;
						goto exit;
					}
				}

				index = atoi(command[1]);
				if(index >= main_hashtable->size) {
					perror("Error: Invalid index.\n");
					result = EXIT_FAILURE;
					goto exit;
				}

				print_bucket(main_hashtable->buckets[index], fout);
			} else if(strcmp(command[0], PRINT) == 0) {
				/* Print the hashtable. */
				for(j = 0; j < main_hashtable->size; ++j)
					print_bucket(main_hashtable->buckets[j], fout);
			} else if(strcmp(command[0], RESIZE) == 0) {
				/* Resize the hashtable. */
				main_hashtable = resize_hashtable(
					&main_hashtable,
					strcmp(command[1], RESIZE_DOUBLE) == 0
						? DOUBLE_MODE
						: HALVE_MODE);
			} else {
				perror("Error: Unknown command.\n");
				result = EXIT_FAILURE;
				goto exit;
			}

			/* Close the output file, if necessary. */
			if(k == 2 || (result == 0 && k == 1)) {
				if(fclose(fout)) {
					perror("Error: Could not close output file.\n");
					result = EXIT_FAILURE;
					goto exit;
				}
			}
		}

		/* No file arguments detected. Read only once, from stdin. */
		if(argc == 2)
			break;
	}

	result = EXIT_SUCCESS;

exit:
	if(main_hashtable)
		free_hashtable(&main_hashtable);
	exit(result);
}