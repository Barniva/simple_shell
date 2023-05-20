#ifndef _SHELL_H
#define _SHELL_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

extern char **environ;

/* Memory Utility */
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_all(char **tokens);

/* String Manipulation */
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
char *_strstr(char *haystack, char *needle);
int _strlen(char *s);
int _atoi(char *s);
char *_strcpy(char *dest, char *src);

/* Execution and Utility */
int execute(char **args);
char *_getenv(char *name);
void print(char *str);
int _putchar(char c);

/* Builtin Commands */
/**
 * struct builtin_s - structure to manage builtin commands
 * @name: name of the command
 * @desc: description of the command
 * @func: function pointer to the associated function
 *
 * Description: This structure manages the builtin commands.
 */
typedef struct builtin_s
{
	char *name;
	char *desc;
	int (*func)(char **args);
} builtin_t;

int cd(char **args);
int help(char **args);
int cexit(char **args);
int env(char **args);
builtin_t *search_builtins(char *command, size_t *count);
void print_builtin_info(builtin_t command);

/* Prompt and Tokenization */
void prompt(char **argv);
char **tokenize(char *command);

#endif /* _SHELL_H */
