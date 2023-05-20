#include <unistd.h>
#include <limits.h>
#include "shell.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * _atoi - convert a string into an integer.
 *
 * @s: the string to use.
 *
 * Return: integer.
 */
int _atoi(char *s)
{
 	int sign = 1, i = 0;
 	unsigned int res = 0;


 	while (!(s[i] <= '9' && s[i] >= '0') && s[i] != '\0')
 	{
 		if (s[i] == '-')
 			sign *= -1;
 		i++;
 	}
 	while (s[i] <= '9' && (s[i] >= '0' && s[i] != '\0'))
 	{
 		res = (res * 10) + (s[i] - '0');
 		i++;
 	}
 	res *= sign;
 	return (res);
}

/**
 * print_num - prints an int
 * @n: int to print
 *
 * Return: number of printed character
 */
int print_num(long n)
{
	unsigned int absolute, aux, countnum, count;

	count = 0;
	if (n < 0)
	{
		absolute = (n * -1);
		count += _putchar('-');
	}
	else
		absolute = n;

	aux = absolute;
	countnum = 1;
	while (aux > 9)
	{
		aux /= 10;
		countnum *= 10;
	}
	while (countnum >= 1)
	{
		count += _putchar(((absolute / countnum) % 10) + '0');
		countnum /= 10;
	}
	return (count);
}

/**
 * print - print str to stdout
 * @s: string to be printed
 */
void print(char *s)
{
	write(STDOUT_FILENO, s, _strlen(s));
}
/**
 * _strcpy - copies the string
 * @dest: destination string
 * @src: source string
 * Return: the pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmp - compares two string
 * @s1: string
 * @s2:  string
 * Return: difference between values of first pair of character
*/
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}

	return ((int)(*s1) - (int)(*s2));
}

/**
 * _strdup - returns a pointer to newly allocated space in
 * memory, which contains a copy of given string
 * @str: string
 * Return: array of character
 */
char *_strdup(char *str)
{
	unsigned int i = 0, size = 0;
	char *ch;

	if (str == NULL)
		return (NULL);

	while (str[size] != '\0')
		size++;

	ch = malloc(sizeof(char) * (size + 1));
	if (ch == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
		ch[i] = str[i];
	ch[i] = '\0';
	return (ch);
}


/**
 * _strcat - concatinates two strings
 * @dest: destination string
 * @src: src string
 * Return: string
*/
char *_strcat(char *dest, char *src)
{
	int i = 0, len = 0;

	while (dest[i] != '\0')
	{
		len++;
		i++;
	}

	i = 0;

	while (src[i] != '\0')
	{
		dest[len + i] = src[i];
		i++;
	}
	dest[len + i] = '\0';

	return (dest);
}

/**
 * _strstr - locates a substring
 * @haystack: string
 * @needle: substring to be located
 * Return:  pointer to the beginning of the located substring,
 * or NULL if the substring is not found.
 */
char *_strstr(char *haystack, char *needle)
{
	int len = 0, i = 0;

	if (*needle == '\0')
	{
		return (haystack);
	}

	while (*(haystack + i) != '\0')
	{
		len++;
		i++;
	}

	for (i = 0; i < len; i++)
	{
		if (*(haystack + i) == *needle)
		{
			char *ptr = _strstr(haystack + i + 1, needle + 1);

			return ((ptr) ? ptr - 1 : NULL);
		}
	}

	return (NULL);
}


/**
 * _strlen - return length of a string
 * @s: string
 * Return: length of string
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i] != '\0')
		i++;
	return (i);
}
