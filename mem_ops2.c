#include <stdlib.h>
#include "shell.h"

/**
 *_memcpy - a function that copies memory area
 *@dest: memory where is stored
 *@src: memory where is copied
 *@n: number of bytes
 *
 *Return: copied memory with n byted changed
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	int r = 0;
	int i = n;


	for (; r < i; r++)
	{
		dest[r] = src[r];
		n--;
	}
	return (dest);
}

/**
 * free_all - frees memory for tokens
 * @tokens: array of string
 */
void free_all(char **tokens)
{
	size_t i;

	if (tokens == NULL)
		return;
	for (i = 0; tokens[i] != NULL; i++)
		free(tokens[i]);

	free(tokens);
}
