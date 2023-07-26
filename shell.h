#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX 1024
#define MAX_COMMANDS 100

void prompt(char **av, char **env);
void exit_shell(int status);
void environment();
char *get_path(char *command);
int handle_semi(char *input, char **commands);
void change_directory(char **av);
int set_environment(char **b);
int unset_environment(char **b);
void handle_comments(char *line);

#endif
