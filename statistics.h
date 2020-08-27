#ifndef STATISTICS_H
#define STATISTICS_H

/**
 * Author: Manuel Cruz
 * Purpose: Declaration of statistics functions
 */

typedef struct
{
	int number_of_lines;
	int number_of_words;
	int number_of_letters;
	char* largest_word;
} statistics_t;

/**
 * Sets the statistics values.
 *
 * @param stats - stats to set value to
 */
void set_statistics(statistics_t* stats);

/**
 * Releases the statistics' word and its memory
 */
void release_statistics(statistics_t* stats);

/**
 * Updates the statistics' with the given word.
 *
 * @param stats - statistics to update
 * @param word - word to include in the stats given
 */
void update_statistics(statistics_t* stats, char* word);

/**
 * Prints the statistics given to the screen.
 *
 * @param stats - statistics to print
 */
void print_statistics(statistics_t* stats);

/**
 * Update the lines in the given stats.
 *
 * @param stats - statistics to update
 */
void update_statistics_lines(statistics_t* stats);

/**
 * Sum the stats of two statistics.
 *
 * @param from - Statistics to grab from
 * @param to - where to include the stats.
 */
void sum_statistics(statistics_t* from, statistics_t* to);

#endif
