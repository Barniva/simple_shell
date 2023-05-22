#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "shell.h"

/**
 * cexit - exits
 * @args: array of strings
 * Return: status
 */
int cexit(char **args)
{
	int status;

	if (args[1] == NULL)
		status = errno;
	else
		status = _atoi(args[1]);

	free_all(args);
	exit(status);
}
/**
 * env - prints enviromental variables
 * @args: array of strings
 * Return: status
 */
int env(char **args __attribute__((unused)))
{
	int i;

	for (i = 0; __environ[i] != NULL; i++)
	{
		print(__environ[i]);
		_putchar('\n');
	}
	return (0);
}
