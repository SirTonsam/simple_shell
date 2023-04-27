#include "shell.h"

/**
 * get_env - searches for an environment variable in a linked list
 * @name: the name of the environment variable to get
 * @env_list: pointer to the head of the environment list
 * Return: a pointer to a string containing the value of the environment
 *	variable or NULL if the variable is not found in the list
 */

char *get_env(char *name, list_t **env_list)
{
	list_t *env_ptr;
	int word_length, index;

	/*get the length of the environment list*/
	env_ptr = *env_list;
	word_length = list_length(env_ptr);

	/*check for the NULL pointers and empty list*/
	if (!env_list || !env_ptr || !name)
		return (NULL);

	/*iterate through the list and search for the given name*/
	index = 0;
	while (index < word_length)
	{
		if (strncmp(env_ptr->str, name, strlen(name)) == 0)
			return (env_ptr->str); /*found the variable, return its value*/
		index++;
		env_ptr = env_ptr->next;
	}
	return (NULL); /*name not found in the environment list*/
}

/**
 * set_env - changes or adds the value of an environment variable
 * @name: the name of the environment variaable to set
 * @value: the new value to be assigned to the environment variable
 * @env_list: pointer to the head of the environment list
 * Return: 0 on success, or 1 on error
 */

int set_env(char *name, char *value, list_t **env_list)
{
	char *new_str, *env_var;
	list_t *ret_node;

	/*create a new string with the variable and value*/
	env_var = create_var_string(name, value);
	if (env_var == NULL)
	{
		perror(ENOMEM);
		return (1);
	}

	/*search for the variable in the environment list*/
	new_str = get_env(name, env_list);
	/*if variable not found, add it to the end of the list*/
	if (new_str == NULL)
	{
		ret_node = add_node_end(env_list, env_var);
		if (ret_node == NULL)
		{
			free(env_var);
			perror(ENOMEM);
			return (1);
		}
		/*free the new string and return success*/
		free(env_var);
		return (0);
	}
	/*if variable found, replace its value*/
	ret_node = get_node(env_list, new_str);
	free(ret_node->str);
	ret_node->str = env_var;
	return (0);
}

/**
 * unset_env - deletes an environment variable from the linked list
 * @name: name name of the environment variable to be deleted
 * @env_list: pointer to the head of the environment list
 * Return: 0 on success, or 1 on error
 */

int unset_env(char *name, list_t **env_list)
{
	char *equal, *env_var;
	int deleted;
	list_t *ptr;

	ptr = *env_list;
	equal = strchr(name, '=');

	/*check if the name is NULL, empty, or contains an '=' character*/
	if ((name == NULL) || ((name[0] == '\0') != 0) || (equal != NULL))
	{
		perror(ENVIL);
		return (1);
	}
	env_var = get_env(name, &ptr);

	if (env_var == NULL) /*variable not found*/
	{
		perror("unsetenv: no such variable\n");
		return (1);
	}
	/*delete the node
