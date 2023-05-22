#include "shell.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>

#define INIT_TOKEN_SIZE 16

/**
 * prompt - prompts user, gets what is typed on the line, executes it
 * @argv - command line arguments
 */

void prompt(char **argv)
{
	char *lineptr = NULL, **tokens;
	size_t n = 0, chars_read;
	int status;

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
	}
}
/**
 * tokenize - split the command in to tokens
 * @command: the command(string) to be tokenized
 * Return: token strings(array)
 */

char **tokenize(char *command)
{
	char *DELIM = " \t\a\r";
	size_t position = 0, toke_size = INIT_TOKEN_SIZE, i;
	char **tokens = malloc(toke_size * sizeof(char *)), *string, *token, **temp;

	if (tokens == NULL)
		return (NULL);
	string = strdup(command);

	if (string == NULL)
	{
		free(tokens);
		return (NULL);
	}

	token = strtok(string, DELIM);

	while (token != NULL)
	{
		tokens[position] = strdup(token);
		if (tokens[position] == NULL)
		{
			for (i = 0; i < position; i++)
			{
				free(tokens[i]);
			}
			free(tokens);
			free(string);
			return (NULL);
		}
		position++;

		if (position >= toke_size)
		{
			toke_size += INIT_TOKEN_SIZE;
			temp = realloc(tokens, toke_size * sizeof(char *));

			if (temp == NULL)
			{
				for (i = 0; i < position; i++)
					free(tokens[i]);
				free(tokens);
				free(string);
				return (NULL);
			}
			tokens = temp;
		}
		token = strtok(NULL, DELIM);
	}

	tokens[position] = NULL;
	free(string);
	return (tokens);
}
/**
 * execute - execute a command
 * @args: array of strings
 * Return: status
 */
int execute(char **args)
{
	pid_t child_pid;
	int status;
	builtin_t builtins[] = {
		{ "cd", "change current working directory: cd [<pathname>]", &cd },
		{ "exit", "exits out of shell: exit [<status>]", &cexit},
		{ "env", "prints environmental variables: env", &env  },
		{ "help", "print information about builtins: help [<command>]", &help}
		};
		size_t i, builtin_count = sizeof(builtins) / sizeof(builtin_t);

	if (args == NULL || args[0] == NULL)
		return (0);

	/* Search for built-in commands */
	for (i = 0; i < builtin_count; i++)
	{
		if (strcmp(args[0], builtins[i].name) == 0)
			return (builtins[i].func(args));
	}

	/*Execute external command*/
	child_pid = fork();
	if (child_pid < 0)
		return (1);

	if (child_pid == 0)
	{
		/*Child process*/
		signal(SIGINT, SIG_DFL); /*Set SIGINT signal handler to default*/
		execvp(args[0], args); /*Execute the command*/
		exit(1); /*If execvp fails, exit the child process*/
	}
	else
	{
		/* Parent process*/
		waitpid(child_pid, &status, WUNTRACED); /*Wait for the child process to terminate*/
		return (status); /*Return the status of the child process*/
	}
}
