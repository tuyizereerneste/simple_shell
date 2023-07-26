#include "shell.h"

/*
 * get_path - Function that checks the path for a command
 * @command: string that is typed in prompt
 * Return: 0 when success, -1 on failure
 */

char *get_path(char *command)
{
	char *path;

	char *path_copy;

	char *path_token;

	char *file_path;

	int command_length;

	int directory_length;

	struct stat buffer;

	path = getenv("PATH");
	if (path)
	{
	path_copy = strdup(path);
	command_length = strlen(command);
	path_token = strtok(path_copy, ":");
	while(path_token != NULL)
	{
	directory_length = strlen(path_token);
	file_path = malloc(command_length + directory_length + 2);
	if (file_path == NULL)
	{
	perror("Memory allocation error");
	free(path_copy);
	return (NULL);
	}
	strcpy(file_path, path_token);
	strcat(file_path, "/");
	strcat(file_path, command);
	strcat(file_path, "\0");
	if (stat(file_path, &buffer) == 0)
	{
	free(path_copy);
	return (file_path);
	}
	else
	{
	free(file_path);
	path_token = strtok(NULL, ":");
	}
	}
	free(path_copy);
	}
	if (stat(command, &buffer) == 0)
	{
	return strdup(command);
	}
	return (NULL);
}
