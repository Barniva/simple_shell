#include "shell.h"
#include <sys/wait.h>

#define INIT_TOKEN_SIZE 16

/**
 * prompt - prompts user, gets what is typed on the line, executes it
 * @av - command line arguments
 * env - enviromental varables
 */

void prompt(char **av, char **env)
{
	char *lineptr = NULL;
	size_t n = 0, chars_read;
	char *argv[INIT_TOKEN_SIZE];
	int i, j, status;
	pid_t c_pid;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("cisfun$ ");
		/*read input from the user*/
		chars_read = getline(&lineptr, &n, stdin);
		/*check if the getline function reached Eof or function is failed*/
		if ((int)chars_read == -1)
		{
			/*free up all allocated memory*/
			free(lineptr);
			exit(EXIT_FAILURE);
		}
		i = 0;

		while (lineptr[i])
		{
			if (lineptr[i] == '\n')
				lineptr[i] = 0;
			i++;
		}

		j = 0;
		/*set the command to be executed using strtok*/
		argv[0] = strtok(lineptr, " ");
		while (argv[j])
			argv[++j] = strtok(NULL, " ");

		c_pid = fork(); /*fork a child process*/
		if (c_pid == -1)
		{
			free(lineptr);
			exit(EXIT_FAILURE);
		}
		if (c_pid == 0)
		{
			/*child process executes the command*/
			if (execve(argv[0], argv, env) == -1)
				printf("%s: No such file or directory\n", av[0]);
		}
		else
		{
			wait(&status); /*parent process waits for child to finish*/
		}
	}
}
