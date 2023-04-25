#include "main.h"
/**
 * main - creates a child process using fork
 * Return: Always returns 0
 */

int main()
{
	pid_t pid = fork();

		if (pid == -1) {
			perror("forking error");
			return (1);
}
		else if (pid == 0) {
			printf ("child process\n");
			return (0);
	} 
		else {
			printf ("parent process and the child's ID is %d\n", pid);
			return (0);
	}
}
