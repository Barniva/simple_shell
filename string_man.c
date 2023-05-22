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
