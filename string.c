#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "string.h"

/**
 * Author: Manuel Cruz
 * Purpose: Nonheader functions definitions of string and header 
 * functions definitions of string
 */

/* ---------------- NonHeader Functions -------- */

/**
 * Checks whether the given char is space or not.
 *
 * @param char_ - char to check for
 * @return true if it is space. false otherwise.
 */
bool is_space(char char_)
{
	return char_ == ' '  || char_ == '\n' ||
		   char_ == '\t' || char_ == '\v' ||
		   char_ == '\f' || char_ == '\r';
}

/**
 * adds a string to a double array.
 *
 * @param array - array to add to
 * @param array_size - current size of the array
 * @param array_capacity - Maximum size of the array
 * @param string - string to add to array
 */
void add_to_double_array(char*** array, int* array_size, int* array_capacity, char* string)
{
	// increase capacity if the current size is equal to the capacity
	if (*array_size == *array_capacity)
	{
		(*array_capacity)++;
		char** new_array = (char**) malloc(sizeof(char*) * (*array_capacity));
		if (new_array == NULL)
		{
			fprintf(stderr, "Cannot add to double array, not enough memory\n");
			exit(MEMORY_ERROR);
		}
		
		// copy values to new array
		for (int i = 0; i < *array_size; ++i)
			new_array[i] = (*array)[i];
		free(*array);
		*array = new_array;
	}
	(*array)[(*array_size)++] = copy_string(string);
}

/* ---------------- Header Functions ----------- */
char** split(char* line, int* size)
{
	if (line == NULL)
	{
		fprintf(stderr, "Cannot split a NULL string\n");
		exit(NULL_ERROR);
	}

	// double array to store
	char** splits = (char**) malloc(sizeof(char*));
	if (splits == NULL)
	{
		fprintf(stderr, "Cannot split creating double array, not enough memory\n");
		exit(MEMORY_ERROR);
	}
	*size = 0;
	int capacity = 1;
	
	char* char_ptr;
	char* token = strtok_r(line, " ", &char_ptr);
	// get words, and add them to the array.
	while (token != NULL)
	{
		add_to_double_array(&splits, size, &capacity, token);
		token = strtok_r(NULL, " ", &char_ptr);
	}
		
	return splits;
}

char* trim_space(char* string)
{
	// check for null
	if (string == NULL)
	{
		fprintf(stderr, "Cannot trim spaces on NULL string\n");
		exit(NULL_ERROR);
	}

	int start = 0;
	int size = string_size(string);
	int end = size - 1;
	
	// first left nonspace char index
	for (int i = 0; i < size; ++i)
	{
		char character = string[i];
		if (!is_space(character))
		{
			start = i;
			break;
		}
	}
	
	// first right nonspace char index
	for (int i = size - 1; i >= 0; --i)
	{
		char character = string[i];
		if (!is_space(character))
		{
			end = i;
			break;
		}
	}
	
	// new string to store the trimmed one
	char* new_string = (char*) malloc(sizeof(char) * (end - start + 2));
	if (new_string == NULL)
	{
		fprintf(stderr, "Cannot trim spaces, out of memeory\n");
		exit(MEMORY_ERROR);
	}
	
	int new_index = 0;
	for (int i = start; i <= end; ++i)
		new_string[new_index++] = string[i];

	new_string[new_index] = '\0'; // null end
	return new_string;
}

char* trim_punctuation(char* string)
{
	if (string == NULL)
	{
		fprintf(stderr, "Cannot trim puntuation on NULL string\n");
		exit(NULL_ERROR);
	}
	
	int start = 0;
	int size = string_size(string);
	int end = size - 1;
	
	// left nonpunctuation char index
	for (int i = 0; i < size; ++i)
	{
		char character = string[i];
		if (!ispunct(character))
		{
			start = i;
			break;
		}
	}
	
	// right nonpunctuation char index.
	for (int i = size - 1; i >= 0; --i)
	{
		char character = string[i];
		if (!ispunct(character))
		{
			end = i;
			break;
		}
	}
	
	// new string to store trimmed one
	char* new_string = (char*) malloc(sizeof(char) * (end - start + 2));
	if (new_string == NULL)
	{
		fprintf(stderr, "Cannot trim punctuation, out of memory\n");
		exit(MEMORY_ERROR);
	}
	
	int new_index = 0;
	for (int i = start; i <= end; ++i)
		new_string[new_index++] = string[i];
	
	new_string[new_index] = '\0'; // null end
	return new_string;
}

char* copy_string(char* string)
{
	int size = string_size(string);
	
	//space for new string copy
	char* new_string = (char*) malloc(sizeof(char) * (size + 1));
	if (new_string == NULL)
	{
		fprintf(stderr, "Cannot copy string, not enough memeory\n");
		exit(MEMORY_ERROR);
	}
	
	for(int i = 0; i <= size; ++i)
		new_string[i] = string[i];
		
	return new_string;
}

int string_size(char* string)
{
	if (string == NULL)
	{
		fprintf(stderr, "Cannot find size of NULL string\n");
		exit(NULL_ERROR);
	}

	int index = 0;
	while (string[index] != '\0')
		index++;
		
	return index;
}

bool equal_string(char* first, char* second)
{
	if (first == NULL || second == NULL)
		return false;

	int first_size = string_size(first);
	int second_size = string_size(second);
	
	if (first_size != second_size)
		return false;
		
	for (int i = 0; i < first_size; ++i)
	{
		if (first[i] != second[i])
			return false;
	}
	
	return true;
}
