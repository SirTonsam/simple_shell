#include "shell.h"

/**
 * prompt - Prints a shell prompt to the standard output stream.
 *
 * This function prints a shell prompt to the standard output stream using
 * the _puts() function from the shell.h header file. It flushes the output
 * buffer using fflush() to ensure that the prompt is printed immediately.
 *
 * Return: void
 */
void prompt(void)
{
	_puts(PROMPT);
	fflush(stdout);
}

