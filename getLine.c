#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t j, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = j; /* init new iterator to current buf position */
		p = buf + j; /* get pointer for return */

		check_chain(info, buf, &j, j, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		j = j + 1; /* increment past nulled ';'' */
		if (j >= len) /* reached end of buffer? */
		{
			j = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @j: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *j)
{
	ssize_t r = 0;

	if (*j)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*j = r;
	return (r);
}

/**
 * _getline - Reads the next line of input
 * from STDIN and returns it as a string.
 * 
 * @info: A pointer to a struct containing
 * information about the program's state.
 * @ptr: A pointer to a pointer to a buffer to hold the
 * input, or NULL to allocate a new buffer.
 * @length: The size of the preallocated buffer, or 0 if ptr is NULL.
 * 
 * Return: A pointer to the input string, or NULL if an error occurs.
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *m;

		p = *ptr;
		if (p && length)
			s = *length;
		if (j == len)
		j = len = 0;

		r = read_buf(info, buf, &len);
		if (r == -1 || (r == 0 && len == 0))
		return (-1);

		m = _strchr(buf + j, '\n');
		k = m ? 1 + (unsigned int)(m - buf) : len;
		new_p = _realloc(p, s, s ? s + k : k + 1);
		if (!new_p) /* MALLOC FAILURE! */
			return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buf + j, k - j);
	else
		_strncpy(new_p, buf + j, k - j + 1);

	s += k - j;
		j = k;
		p = new_p;

		if (length)
		*length = s;
		*ptr = p;
		return (s);
}

/**
 * sigintHandler - blocks ctrl-m
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
