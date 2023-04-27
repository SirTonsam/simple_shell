#include "shell.h"

/**
 * cmd_line_loop - Reads user input and executes commands until the user
 *                 exits or encounters an EOF (ctrl^D).
 *
 * @buffer: Pointer to a buffer to store the input from the user.
 * @line: Pointer to a string containing the user's input.
 * @env_head: Pointer to the head of the environment list.
 *
 * Return: 0 on success, or 1 if _realloc failed.
 */
int cmd_line_loop(char *buffer, char *line, list_t **env_head)
{
    list_t *env_list_ptr;
    int input_len, old_len, retval = 0;
    char **token;

    env_list_ptr = *env_head;

    /* Continuously loop until the user types "exit" or encounters an EOF (Ctrl-D) */
    while (1)
    {
        clear_buffer(buffer); /* Clear the buffer to receive new input */

        /* Read input from the user */
        input_len = _getline(buffer, BUFF_SIZE);

        /* If _getline() returns -1, the user has encountered an EOF, so break the loop */
        if (input_len == -1)
            break;

        /* Resize the line buffer to accommodate the new input */
        if (line == NULL)
            old_len = 0;
        else
            old_len = _strlen(line);

        line = _realloc(line, old_len, ++input_len);

        /* If _realloc() fails, set retval to 1, print an error message, and break the loop */
        if (line == NULL)
        {
            perror("ENOMEM");
            retval = 1;
            break;
        }

        /* Copy the contents of the buffer into the memory pointed to by line */
        line = mem_cpy(line, buffer, input_len);

        if (line[0] != '\0')
        {
            /* Split the input into an array of tokens */
            token = strtow(line, ' ');

            /* Check if the user has entered one of the built-in shell commands */
            retval = built_ins(token, &env_list_ptr);

            /* Check if the user has entered the "exit" command, and exit the shell if so */
            if (exit_shell(token) && retval != -1)
            {
                free_array(token);
                break;
            }

            /* If the command is not a built-in, execute it as an external command */
            if (retval == -1)
                retval = execute_command(token, &env_list_ptr);

            /* Free the token array */
            free_array(token);
        }
    }

    /* Free the line buffer and return the result */
    free(line);
    return (retval);
}
