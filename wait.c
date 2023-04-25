#include "shell.h"

/**
 * wait - parent to wait for the child to process
 * Return: on success, return PID child process
 * Return -1 on error
 */

pid_t wait(int *status)
{
	pid_t pid;

do
	{
		pid = waitpid(-1, status,0);
	}
	while (pid == -1 && errno == EINTR);

	return pid;
}
