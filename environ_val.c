#include "shell.h"

extern char **environ;

/*
 * environment - Function that prints the current environment
 *
 * Return: Nothing
 */

void environment()
{
	char **ptr = environ;

	while (*ptr != NULL)
	{
	printf("%s\n", *ptr);
	ptr++;
	}
}
