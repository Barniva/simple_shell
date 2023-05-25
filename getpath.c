#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "shell.h"

/**
 * getpath - gets path
 * @str: path key
 * Return: get path
 */
char *getpath(char **str)
{
	char *path, *tok, *cmd;
	struct stat statbuf;

	if (stat(*str, &statbuf) == 0)
		return (*str);
	path = _getenv("PATH");
	tok = strtok(path, ":");
	while (tok)
	{
		cmd = malloc(sizeof(char) * (strlen(tok) + strlen(*str) + 2));
		strcpy(cmd, tok);
		strcat(cmd, "/");
		strcat(cmd, *str);
		if (stat(cmd, &statbuf) == 0)
		{
			free(path);
			free(*str);
			*str = cmd;
			return (cmd);
		}
		free(cmd);
		tok = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}
