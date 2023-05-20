#include "shell.h"
#include <sys/wait.h>

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
        argv[0] = lineptr;
        c_pid = fork();
        if (c_pid == -1)
	{
		free(lineptr);
        	exit(EXIT_FAILURE);
        }
        if (c_pid == 0)
        {
        	if (execve(argv[0], argv, env) == -1)
                	printf("%s: No such file or directory\n", av[0]);
        }
        else
        {
        	wait(&status);
        }
    }
}
