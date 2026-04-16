#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* shell.c */
char *read_line(int *eof);
char **split_line(char *line);
int execute(char **args, char *prog_name);

/* path.c */
char *find_in_path(char *cmd);
char *build_path(char *dir, char *cmd);

/* builtins.c */
int handle_builtin(char **args);

/* utils.c */
void free_args(char **args);
int is_empty(char *line);

#endif /* SHELL_H */
