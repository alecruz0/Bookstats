#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "statistics.h"
#include "string.h"

/**
 * Author: Manuel Cruz
 * Purpose: Definition of statistics functions
 */

void set_statistics(statistics_t* stats)
{
	// sets value of stats given
	stats->number_of_lines = 0;
	stats->largest_word = NULL;
	stats->number_of_words = 0;
	stats->number_of_letters = 0;
}

void release_statistics(statistics_t* stats)
{
	if (stats == NULL)
	{
		fprintf(stderr, "Cannot destroy a NULL stat\n");
		exit(NULL_ERROR);
	}
	
	if (stats->largest_word != NULL)
		free(stats->largest_word); // free the word
}

void update_statistics_lines(statistics_t* stats)
{
	stats->number_of_lines++;
}

void update_statistics(statistics_t* stats, char* word)
{
	if (stats == NULL)
	{
		fprintf(stderr, "Cannot update NULL statistics\n");
		exit(NULL_ERROR);
	}
	
	if (word == NULL)
	{
		fprintf(stderr, "Cannot update statistics with NULL word\n");
		exit(NULL_ERROR);
	}
	
	// updates the number of words
	stats->number_of_words++;
	int word_size = string_size(word);
	stats->number_of_letters += word_size;
	
	// update the largest word
	int largest_word_size;
	if (stats->largest_word != NULL)
		largest_word_size = string_size(stats->largest_word);
	else
		largest_word_size = 0;
		
	if (word_size > largest_word_size)
	{		
		if (stats->largest_word != NULL)
			free(stats->largest_word);
		stats->largest_word = copy_string(word);
	}
}

void print_statistics(statistics_t* stats)
{
	printf("STATISTICS:\n");
	printf("\tNumber of Lines: %d\n", stats->number_of_lines);
	printf("\tNumber of Words: %d\n", stats->number_of_words);
	printf("\tNumber of Letters: %d\n", stats->number_of_letters);
	printf("\tLargest Word Size: %d\n", string_size(stats->largest_word));
	printf("\tLargest Word: %s\n", stats->largest_word);
}

void sum_statistics(statistics_t* from, statistics_t* to)
{
	to->number_of_lines += from->number_of_lines;
	to->number_of_words += from->number_of_words;
	to->number_of_letters += from->number_of_letters;
	
	if (to->largest_word != NULL)
	{
		if (string_size(from->largest_word) > string_size(to->largest_word))
		{
			free(to->largest_word);
			to->largest_word = copy_string(from->largest_word);
		}
	}
	else
		to->largest_word = copy_string(from->largest_word);
}

