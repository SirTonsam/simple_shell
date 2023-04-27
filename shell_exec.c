#include "shell.h"

/**
 * cmd_line_loop - Reads user input and executes commands until user enters
 * "exit" or EOF (ctrl^D)
 * @buffer: Buffer to store user input
 * @line: Pointer to a string of the current line input
 * @env_head: Pointer to the head of the environment list
 *
 * Return: 0 on success, or 1 if _realloc failed
 */
int cmd_line_loop(char *buffer, char *line, list_t **env_head)
{
	list_t *env_list_ptr;
	int input_len, old_length, retval = 0;
	char **token;

	env_list_ptr = *env_head;

	/* Continuously loop until user enters "exit" or EOF (Ctrl-D) */
	while (1)
	{
		clear_buffer(buffer); /* Clear the buffer for new input */

		/* Read input from user */
		input_len = _getline(buffer, BUFF_SIZE);

		/* If chars_read is -1, the user has entered EOF, so break the loop */
		if (input_len == -1)
			break;

		if (line == NULL)
			old_length = 0;
		else
			old_length = _strlen(line);

		/* Resize line buffer */
		line = _realloc(line, old_length, ++input_len);

		/* If _realloc fails, print error message, set retval to 1, and break loop */
		if (line == NULL)
		{
			perror("ENOMEM");
			retval = 1;
			break;
		}

		/* Copy input into line buffer */
		line = mem_cpy(line, buffer, input_len);

		if (line[0] != '\0')
		{
			/* Tokenize the input string */
			token = strtow(line, ' ');

			/* Check for built-in commands */
			retval = built_ins(token, &env_list_ptr);

			/* If user enters "exit" and retval is not -1, break loop */
			if (exit_shell(token) && retval != -1)
			{
				free_array(token);
				break;
			}

			/* If input is not a built-in command, execute it */
			if (retval == -1)
				retval = execute_command(token, &env_list_ptr);

			free_array(token);
		}
	}

	/* Free the memory allocated for the line buffer */
	free(line);
	return (retval);
}
