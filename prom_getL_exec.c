#include "shell.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>

#define INIT_TOKEN_SIZE 16

/**
 * prompt - prompts user, gets what is typed on the line, executes it
 * @argv: command line arguments
 */

void prompt(char **argv)
{
	char *lineptr = NULL, **tokens;
	size_t n = 0, chars_read;
	int status;

	signal(SIGINT, SIG_IGN);
	do
	{
		fflush(NULL);
		if (isatty(STDIN_FILENO))
			printf(":) ");
		/*read input from the user*/
		chars_read = getline(&lineptr, &n, stdin);
		/*check if the getline function reached Eof or function is failed*/
		if ((int)chars_read == -1)
		{
			/*free up all allocated memory*/
			free(lineptr);
			exit(EXIT_FAILURE);
		}

		if ((int)chars_read < 0)
			break;
		lineptr[chars_read - 1] = '\0';
		tokens = tokenize(lineptr);
		if (lineptr != NULL)
		{
			free(lineptr);
			lineptr = NULL;
		}
		/*takes array of strings retruned by the tokenizer and executes it*/
		status = execute(tokens);
		if (status != 0)
			perror(argv[0]);
		free(tokens);
	}while(1);
	if (lineptr != NULL)
		free(lineptr);
}
/**
 * tokenize - split the command in to tokens
 * @command: the command(string) to be tokenized
 * Return: token strings(array)
*/
char **tokenize(const char *command)
{
	char **tokens = NULL;
	char *token;
	char *str = strdup(command);
	const char *DELIM = " \t\a\r";
	size_t position = 0;
	size_t tokenArraySize = INIT_TOKEN_SIZE;

	tokens = malloc(tokenArraySize * sizeof(char *));
	if (tokens == NULL)
	return (NULL);

	token = strtok(str, DELIM);
	while (token != NULL)
	{
	tokens[position++] = strdup(token);
	if (position >= tokenArraySize)
	{
		tokenArraySize += INIT_TOKEN_SIZE;
		tokens = realloc(tokens, tokenArraySize * sizeof(char *));
		if (tokens == NULL)
		{
		while (position > 0)
			free(tokens[--position]);
		free(tokens);
		return (NULL);
		}
	}
	token = strtok(NULL, DELIM);
	}
	tokens[position] = NULL;
	free(str);
	return (tokens);
}
/**
 * execute - execute a command
 * @args: array of strings
 * Return: always 0 on sucess
 */
int execute(char **args)
{
	pid_t child_pid;
	int status;
	size_t i, builtin_count;
	builtin_t builtins[] = {
	{"cd", "change current working directory: cd [<pathname>]", &cd},
	{"exit", "exits out of shell: exit [<status>]", &cexit},
	{"env", "prints environmental variables: env", &env},
	{"help", "print information about builtins: help [<command>]", &help}
	};
	builtin_count = sizeof(builtins) / sizeof(builtin_t);

i	if (args == NULL || args[0] == NULL)
		return (0);
	for (i = (0); i < builtin_count; i++)
	{
		if (strcmp(args[0], builtins[i].name) == 0)
			return (builtins[i].func(args));
	}
	if (getpath(&args[0]) == NULL)
		return (1);
	child_pid = fork();
	if (child_pid < 0)
		return (1);
	if (child_pid == 0)
	{
		signal(SIGINT, SIG_DFL); /* Set SIGINT signal handler to default*/
		if (execve(args[0], args, __environ) < 0)
			return (1);
	}
	else
	{
		wait(&status); /* Wait for the child process to finish*/
	}
	return (status); /*Return the status of the child process*/
}
