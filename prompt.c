#include "shell.h"
#include <sys/wait.h>

/**
 * prompt - prompts user to enter a command gets what is typed on the line and executes it
 * @av - command line arguments
 * env - enviromental varables
 */

void prompt(char **av, char **env)
{
    char *lineptr = NULL;
    size_t n = 0, chars_read;
    char *argv[] = {NULL, NULL};
    int i, status;
    pid_t c_pid;

    while (1)
    {
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
        	if (lineptr[i] =='\n')
        		lineptr[i] = 0;
		i++;
        }
	/*set the command to be executed*/
        argv[0] = lineptr; /*fork a child process*/
        c_pid = fork();
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
