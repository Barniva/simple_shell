#include "shell.h"

/**
 * main - every thig starts here
 * 
 * return - always return 0
 */
int main(int ac, char **av, char **env __attribute((unused)))
{
    if (ac == 1)
    {
        prompt(av);
    }
    return (0);
}
