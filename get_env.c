#include "shell.h"

/**
 * _getenv - Gets the value of an environment variable
 * @name: The name of the environment variable to look up
 *
 * This function retrieves the value of an environment variable based on its
 * name. It iterates through the list of environment variables stored in the
 * global variable `environ`, checking each variable to see if its name matches
 * the input parameter `name`. If a match is found, it returns the value of the
  *environment variable.
 * Otherwise, it returns NULL to indicate that the variable
 * does not exist.
 * @name: The name of the environment variable to look up
 * Return: A pointer to the value of the environment variable, or NULL if the
 * variable does not exist
 */
char *_getenv(const char *name)
{
	char **env;
	size_t name_len = _strlen(name);
/*
 * Iterate through the list of environment variables
*/
	for (env = environ; *env != NULL; env++)
	{
/*
 * Check if the name of the environment
* variable matches the input name
*/
		if (_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{
/*
 * Return a pointer
 *to the value of the environment variable
 */
		return (&(*env)[name_len + 1]);
		}
	}
	/*
	 * If no match is found, return NULL to indicate that
	*the variable does not exist
	*/
	return (NULL);
}
