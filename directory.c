#include "shell.h"

/*
 * change_directory - Function that implement the cd builtin command
 * @av: argument that is given to cd command
 * Return: 0 when success, -1 when fail
 */

void change_directory(char **av)
{
	char *directory;

	char *current_directory;

	char *new_pwd;

	directory = av[1];
	if (directory == NULL || strcmp(directory, "") == 0)
	{
	directory = getenv("HOME");
	}
	else if (strcmp(directory, "-") == 0)
	{
	directory = getenv("OLDPWD");
	if (directory == NULL)
	{
	return;
	}
	}
	current_directory = getcwd(NULL, 0);
	if (current_directory != NULL)
	{
	setenv("OLDPWD", current_directory, 1);
	free(current_directory);
	}
	if (chdir(directory) != 0)
	{
	perror("cd");
	}
	else
	{
	new_pwd = getcwd(NULL, 0);
	if (new_pwd != NULL)
	{
	setenv("PWD", new_pwd, 1);
	free(new_pwd);
	}
	}
}
