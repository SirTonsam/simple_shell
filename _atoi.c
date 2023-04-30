#include "shell.h"

/**
 * interactive - Checks if the program is running in interactive mode,
 *                i.e., whether it is connected to a terminal or not.
 * 
 * @info: Pointer to a structure containing information about the program
 *        environment.
 * 
 * Return: 1 if running in interactive mode, 0 otherwise.
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checks if a given character is a delimiter by comparing it to
 *            a string of delimiters.
 * 
 * @m: The character to be checked.
 * @delmtr: The string of delimiter characters to compare against.
 * 
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */

int is_delim(char m, char *delmtr)
{
	while (*delmtr)
		if (*delmtr++ == m)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@m: The character to input
 *Return: 1 if m is alphabetic, 0 otherwise
 */

int _isalpha(int m)
{
	if ((m >= 'a' && m <= 'z') || (m >= 'A' && m <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int j, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (j = 0;  s[j] != '\0' && flag != 2; j++)
	{
		if (s[j] == '-')
			sign *= -1;

		if (s[j] >= '0' && s[j] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[j] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
