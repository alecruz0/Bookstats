#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>

#include "constants.h"
#include "bookstats.h"
#include "string.h"
#include "queue.h"
#include "statistics.h"
#include "line.h"

/**
 * Author: Manuel Cruz
 * Date: August 10, 2020
 * Purpose: Given a text file, generate statistics of the text in it.
 */

int       thread_number; // number of threads
sem_t     semaphore; // semaphore of queue and done bool
queue_t   queue; // queue to communicate among threads
bool 	  done; // done bool of main thread

/**
 * Main starting point of the program.
 *
 * @param argc - Number of arguments sent
 * @param argv - Array of arguments
 *
 * @return the exit status of the program
 */
int main(int argc, char* argv[])
{
	//Checks the number of args sent. Must be 3.
	if (argc != 3)
	{
		usage();
		return INVALID_ARGS;
	}
	
	char* filename = argv[2]; // get filename
	thread_number = atoi(argv[1]); // get number of threads
	
	// make sure at least one thread gets used
	if (thread_number < 1)
	{
		usage();
		return INVALID_THREAD_COUNT;
	}
	
	// open file to read
	FILE* file_pointer = fopen(filename, "r");
	if (file_pointer == NULL)
	{
		fprintf(stderr, "Unable to open file: %s\n", filename);
		return OPEN_FILE_FAILURE;
	}
	
	// check file is not empty
	fseek(file_pointer, 0, SEEK_END);
	long file_size = ftell(file_pointer);
	if (file_size < 1)
	{
		fprintf(stderr, "File: %s, is empty\n", filename);
		return EMPTY_FILE;
	}
	fseek(file_pointer, 0, SEEK_SET);
	
	// create storage for threads
	pthread_t threads[thread_number];
	
	// create 
	sem_init(&semaphore, 0, 1);
	set_queue(&queue); // set queue for threads to receive
	done = false; // set we not done yet
	
	// create threads
	for (long i = 0; i < thread_number; ++i)
		pthread_create(&threads[i], NULL, thread, NULL);
		
	ssize_t length = 0;
	char* line = NULL;
	int count = 0;
	
	/*
	 * Reads every line, and puts it on the queue for
	 * threads to pop them and process them
	 */
	int read = getline(&line, &length, file_pointer);
	while (read != -1)
	{
		line_t* struct_line = create_line(line, ++count);
		
		sem_wait(&semaphore);
		push(&queue, (void*) struct_line);
		sem_post(&semaphore);
		read = getline(&line, &length, file_pointer);
	}
	
	free(line); // free last line read
	fclose(file_pointer); // close file
	
	
	// tell threads every line has been processed
	sem_wait(&semaphore);
	done = true;
	sem_post(&semaphore);
	
	// set statistics to be received from threads
	statistics_t sum_stats;
	set_statistics(&sum_stats);
	for (int i = 0; i < thread_number; ++i)
	{
		// receive stats from thread
		statistics_t* stats;
		pthread_join(threads[i], (void*) &stats);
		
		// sum it
		sum_statistics(stats, &sum_stats);
		
		// release it
		release_statistics(stats);
		
		// free it
		free(stats);
	}
	
	// release semaphore
	sem_close(&queue_semaphore);
	
	release_queue(&queue); // release queue
	print_statistics(&sum_stats); // print stats to screen
	release_statistics(&sum_stats); // release sum of stats
	
	return SUCCESS;
}

void* thread(void* parameters)
{
	// create a stat to keep track of the lines processed
	statistics_t* stats = (statistics_t*) malloc(sizeof(statistics_t));
	if (stats == NULL)
	{
		fprintf(stderr, "Cannot create stats in thread, not enough memory\n");
		exit(MEMORY_ERROR);
	}
	
	// set the stats
	set_statistics(stats);
	
	while (true)
	{
		// check that we are not done and the queue is not empy
		// leave only when we are done and there are no more lines to process
		sem_wait(&semaphore);
		if (done && is_empty(&queue))
		{
			sem_post(&semaphore);
			break;
		}
		
		line_t* line = NULL;
		if (!is_empty(&queue))
		{
			// pop a line
			line = (line_t*) pop(&queue);
			sem_post(&semaphore);
			
			if (line != NULL)
			{
				int size;
				// split the line
				char** line_split = split(line->line, &size);
				if (line_split != NULL)
				{
					// process each word
					for (int i = 0; i < size; ++i)
					{
						// split the line
						char* current_line = line_split[i];
						line_split[i] = trim_space(current_line);
						free(current_line);
						
						// remove punctuation
						current_line = line_split[i];
						line_split[i] = trim_punctuation(line_split[i]);
						free(current_line);
						
						// update stats of this thread
						update_statistics(stats, line_split[i]);
						free(line_split[i]);
					}
					free(line_split);
				}
				destroy_line(line);
				
				// increase line count
				update_statistics_lines(stats);
			}
		}
		else
			sem_post(&semaphore);
	}
	
	// return the stats of this thread
	// to main thread
	return stats;
}

void usage()
{
	printf("Usage:\n");
	printf("\t./bookstats <number of threads> <text file to read>\n");
	printf("\t<number of threads> - Cannot be less than 1\n");
	printf("\t<text file to read> - must be a valid text file\n");
}

