#ifndef STRING_H
#define STRING_H

#include <stdbool.h>

/**
 * Author: Manuel Cruz
 * Purpose: Header functions of string declarations
 */

/**
 * Splits a string by spaces.
 * Warning: Every single string in the array points to the heap.
 * Warning: The string array points to the heap
 *
 * @param line - String to be split
 * @param size - pointer to place the size of the string array returned
 *
 * @return an array of strings
 */
char** split(char* line, int* size);

/**
 * Trims the space in front and back of the string.
 * Warning: The returned string points to the heap.
 *
 * @param string - string to be trimmed
 *
 * @return new string trimmed
 */
char* trim_space(char* string);

/**
 * Trims the punctuation of a string in the front and back.
 * Warning: The returned string points to the heap
 *
 * @param string - string to trim punctuation from
 *
 * @return new string trimmed
 */
char* trim_punctuation(char* string);

/**
 * Creates a deep copy of the given string.
 * Warning: The new string points to the heap
 *
 * @param string - string to deep copy
 *
 * @return a new copy of the string
 */
char* copy_string(char* string);

/**
 * Gets the size of a string. It counts until it find the null char.
 * It does not count the null char as part of the string.
 *
 * @param string - string to get size
 *
 * return size of string
 */
int string_size(char* string);

/**
 * Checks whether two strings are the same or not.
 * It first checks their sizes.
 * If they have the same size then, it checks each individual character.
 * If it doesn't find two different characters in position, then they must be equal.
 *
 * @param first - first string to compare
 * @param second - second string to compare
 *
 * @return true if they both are equal, false otherwise.
 */
bool equal_string(char* first, char* second);

#endif
