#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int j, j;
	char *s = dest;

	j = 0;
	while (src[j] != '\0' && j < n - 1)
	{
		dest[j] = src[j];
		j++;
	}
	if (j < n)
	{
		j = j;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int j, j;
	char *s = dest;

	j = 0;
	j = 0;
	while (dest[j] != '\0')
		j++;
	while (src[j] != '\0' && j < n)
	{
		dest[j] = src[j];
		j++;
		j++;
	}
	if (j < n)
		dest[j] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@m: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char m)
{
	do {
		if (*s == m)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
