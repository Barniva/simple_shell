#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "shell.h"

/**
 * cd - change current working directory
 * @args: array of strings
 * Return: status
 */
int cd(char **args)
{
	int status;
	char *pwd = NULL;

	if (args[1] == NULL)
	{
		pwd = _getenv("HOME");
		status = chdir(pwd);
	}
	else if (_strcmp(args[1], "-") == 0)
	{
		pwd = _getenv("OLDPWD");
		status = chdir(pwd);
	}
	else
		status = chdir(args[1]);
	free(pwd);
	return (status);
}
/**
 * printBuiltins - prints builtins
 * @b: builtin
 */
void printBuiltins(builtin_t b)
{
	print(b.name);
	print("\t: ");
	print(b.desc);
	print("\n");
}
