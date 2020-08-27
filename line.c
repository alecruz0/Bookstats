#include <stdio.h>
#include <stdlib.h>

#include "line.h"
#include "constants.h"
#include "string.h"

/**
 * Author: Manuel Cruz
 * Purpose: Definition of header functions for line
 */

line_t* create_line(char* line, int line_number)
{
	// get memory for the struct
	line_t* structure = (line_t*) malloc(sizeof(line_t));
	if (structure == NULL)
	{
		fprintf(stderr, "Cannot create line structure, not enough memory\n");
		exit(MEMORY_ERROR);
	}
	
	// copy line
	structure->line = copy_string(line);
	
	// set line number
	structure->line_number = line_number;
	
	return structure;
}

void destroy_line(line_t* line)
{
	// release memory of line
	free(line->line);
	
	// release line in general
	free(line);
}
