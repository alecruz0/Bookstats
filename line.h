#ifndef LINE_H
#define LINE_H

/**
 * Author: Manuel Cruz
 * Purpose: Line definition and liner header functions declarations
 */

typedef struct
{
	char* line; // line of structutre
	int line_number; // line number
} line_t;

/**
 * Creates line to be processed
 *
 * @param line - Line to process
 * @param line_number - number line in file
 */
line_t* create_line(char* line, int line_number);

/**
 * Releases the memory of the given line
 */
void destroy_line(line_t* line);

#endif
