#ifndef BOOKSTATS_H
#define BOOKSTATS_H

/**
 * Author: Manuel Cruz
 * Purpose: Header of main functions declarations
 */

/**
 * Thread function to process a line from the file.
 *
 * @param parameters - parameters sent to the thread
 * @return stats of the lines processed
 */
void* thread(void* parameters);

/**
 * Prints usage of this program
 */
void usage();

#endif
