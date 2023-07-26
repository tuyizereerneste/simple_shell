#include "shell.h"

/*
 * set_environment - function that Implements setenv builtin command
 * @b: string that contain variable value
 * Return: 0 when success, -1 on fail
 */

int set_environment(char **b)
{
	if (b[1] == NULL || b[2] == NULL)
	{
	perror("setenv Failed");
	return (-1);
	}
	if (setenv(b[1], b[2], 1) != 0)
	{
	perror("Failed to set environment variable");
	return (-1);
	}
	return (0);
}

/*
 * unset_environment - Function that implements unsetenv command
 * @b: string that contain variable value
 * Return: 0 when success, -1 on failure
 */

int unset_environment(char **b)
{
	if (b[1] == NULL)
	{
	perror("unsetenv Failed");
	return (-1);
	}
	if (unsetenv(b[1]) != 0)
	{
	perror("Failed to unset environment variable");
	return (-1);
	}
	return (0);
}
