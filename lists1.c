#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t j = 0;
while (h)
	{
	h = h->next;
	j++;
}
	return (j);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t j = list_len(head), j;
	char **strs;
	char *str;
if (!head || !j)
	return (NULL);
strs = malloc(sizeof(char *) * (j + 1));
if (!strs)
	return (NULL);
for (j = 0; node; node = node->next, j++)
{
	str = malloc(_strlen(node->str) + 1);
	if (!str)
	{
		for (j = 0; j < j; j++)
			free(strs[j]);
		free(strs);
		return (NULL);
	}
	str = _strcpy(str, node->str);
	strs[j] = str;
	}
strs[j] = NULL;
	return (strs);
}


/**
 * prnt_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t prnt_list(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(convert_number(h->nmbr, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @m: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char m)
{
char *p = NULL;
while (node)
{
	p = starts_with(node->str, prefix);
	if (p && ((m == -1) || (*p == m)))
	return (node);
	node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Returns the index of a node in a linked list.
 * 
 * @head: A pointer to the head of the linked list.
 * @node: A pointer to the node whose index is being sought.
 * 
 * Return: The index of the node within the linked list, or -1 if the node is
 *         not found in the list.
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
	if (head == node)
		return (j);
	head = head->next;
	j++;
	}
	return (-1);
}
