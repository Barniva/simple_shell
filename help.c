#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "shell.h"

/**
 * help - print help
 * @args: array of strings
 * Return: status
 */
int help(char **args)
{
	int i;
	builtin_t builtins[] = {
			{ "cd", "change current working directory: cd [<pathname>]", &cd },
			{ "exit", "exits out of shell: exit [<status>]", &cexit},
			{ "env", "prints enviromental variables: env", &env  },
			{ "help", "print information about builtins: help [<command>]", &help}
	};
	int builtin_count = sizeof(builtins) / sizeof(builtin_t);

	if (args[1] != NULL)
	{
		for (i = 0; i < builtin_count; i++)
			if (_strcmp(args[1], builtins[i].name) == 0)
			{
				printBuiltins(builtins[i]);
				break;
			}
		if (builtins[i].name == NULL)
		{
			print(args[1]);
			print("Not a builtin command\n");
			return (1);
		}
	}
	else
	{
		print("Simple Shell\nThe following are built in:\n");
		for (i = 0; i < builtin_count; i++)
			printBuiltins(builtins[i]);
		print("Use man for other commands\n");
	}
	return (0);
}
