#include "shell.h"

/* prompt - Function that prompts the user for input,
 * reads the input line, and executes
 * the commands entered by the user.
 * @av: is the argument vector
 * @env: are arrays of strings representing the arguments 
 * and environment variables 
 * Return 0 when success, -1 on failure
 */

void prompt(char **av, char **env)
{
	char *line = NULL;

	int i, n, status;

	size_t bufsize = 0;

	char *argv[MAX];

	pid_t child_pid;

	int arg_status;

	char *command;

	size_t length;

	while (1)
	{
	if (isatty(STDIN_FILENO))
	printf("#cisfun$ ");
	if ((getline(&line, &bufsize, stdin) == -1))
	{
	free (line);
	exit(EXIT_FAILURE);
	}

	length = strlen(line);
	if (length > 0 && line[length - 1] == '\n')
	line[length - 1] = '\0';
	i = 0;
	while(line[i])
	{
	if (line[i] == '\n')
	line[i] = '\0';
	i++;
	}
	n = 0;
	argv[n] = strtok(line, " ");
	while (argv[n])
	{
	n++;
	argv[n] = strtok(NULL, " ");
	}

	/* Let's exit the shell if exit is the input*/

	if (strcmp(argv[0], "exit") == 0)
	{
	if (n >= 2)
	{
	arg_status = atoi(argv[1]);
	exit_shell(arg_status);
	}
	else
	{
	exit_shell(0);
	}
	break;
	}
	
	/* Let's check if the input is env to 
	 * print current environment
	 */

	else if (strcmp(argv[0], "env") == 0)
	{
		environment();
	}

	/*Let's check if the input is cd to
	 * print or change directory
	 */

	else if (strcmp(argv[0], "cd") == 0)
	{
	change_directory(argv);
	}

	/*Let's check if the input is setenv to 
	 * set environment variable
	 */

	else if (strcmp(argv[0], "setenv") == 0)
	{
	if (set_environment(argv) == -1)
	{
	perror("Failed to set environment variable");
	}
	}

	/*Let's check if the input is unsetenv to
	 * unset environment variable
	 */

	else if (strcmp(argv[0], "unsetenv") == 0)
	{
	if (unset_environment(argv) == -1)
	{
	perror("Failed to set environment variable");
	}
	}
	else
	{
	command = get_path(argv[0]);
	if (command != NULL)
	{
	child_pid = fork();
	if (child_pid == -1)
	{
	perror("Folk failed");
	free(line);
	exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
	if (execve(command, argv, env) == -1)
	{
	perror("execve Failed");
	exit(EXIT_FAILURE);
	}
	}
	else
	{
	waitpid(child_pid, &status, 0);
	}
	free(command);
	}
	else
	{
	printf("%s: No such file or directory\n", av[0]);
	}
	}
	}
}
