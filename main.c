#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * This function is the main entry point of the shell program. It is responsible
 * for initializing variables, allocating memory, and calling the command line
 * loop function to execute the shell.
 *
 * Return: 0 on success, otherwise an error code
 */

int main(void)
{
	char *input, *cmd;  /* pointers to character arrays for input and command */
	list_t *env_list;   /* pointer to a linked list to hold environment variables */
	int status;         /* integer to store the status of the command line loop */

	/* Allocate memory for the input buffer using malloc() */
	input = malloc(sizeof(char) * BUFF_SIZE);

	/* Check if memory was allocated successfully */
	if (input == NULL)
		return (1);  /* Return an error code if memory allocation failed */

	cmd = NULL;  /* Set the command pointer to NULL */

	/* Convert the environment variables array into a linked list */
	env_list = array_to_list(environ);

	/* Call the command line loop function and store the return status */
	status = cmd_line_loop(input, cmd, &env_list);

	/* Free the memory allocated for the linked list and input buffer */
	free_list(env_list);
	free(input);

	/* Return the status of the command line loop to the calling function */
	return (status);
}
