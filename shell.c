#include "shell.h"

/**
 * main - Entry point of the program
 * @ac: The number of command-line arguments
 * @av: An array of strings containing the command-line arguments
 * @env: environment variables (unused)
 *
 * Return: The exit status of the program (0 for successful execution)
 */

int main(int ac, char **av, char **env __attribute__((unused)))
{
	if (ac == 1)
	{
		prompt(av);
	}
	return (0);
}
