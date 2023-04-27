#include "shell.h"

/**
 * get_line - Reads a line of input from standard input.
 *
 * This function reads input from the standard input
 * (i.e., keyboard) and stores
 * it in a buffer of size BUFFER_SIZE. The input is read in chunks of size
 * BUFFER_SIZE, and the buffer is dynamically resized as necessary to store the
 * entire input string.
 *
 * Return: A pointer to the input string entered by the user, or NULL if an
 * error occurred.
 */
void *get_line(void)
{
	static char buffer[BUFFER_SIZE]; /* Static buffer to store input*/
	static int buf_pos, buf_size;    /*Position and size of buffer*/
	char *input_str = NULL;          /*Pointer to input string*/
	char current_char;               /*Current character being read*/
	int input_len = 0;               /*Length of input string*/

	/* Loop indefinitely until input is received*/
	while (1)
	{
	if (buf_pos >= buf_size)
	{
	buf_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
	buf_pos = 0;

	if (buf_size == 0)
	return (input_str);
	/* If there was an error reading input, return NULL*/
	else if (buf_size < 0)
	{
	perror("read");
	return (NULL);
	}
	}
	current_char = buffer[buf_pos];
	buf_pos++;

	 /*If end of line, resize input string and return*/
	if (current_char == '\n')
	{
	input_str = realloc(input_str, input_len + 1);
	input_str[input_len] = '\0';
	return (input_str);
	}
	else
	{
	input_str = realloc(input_str, input_len + 1);
	input_str[input_len] = current_char;
	input_len++;
}
}
}
