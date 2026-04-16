#ifndef MAIN_H
#define MAIN_H

/* Prototypes des fonctions utilisées dans main.c */
char *read_line(int *eof);
int is_empty(char *line);
char **split_line(char *line);
void free_args(char **args);
int handle_builtin(char **args);
int execute(char **args, char *prog_name);

#endif
