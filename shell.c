#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Simple shell logic with argument handling
 * @ac: Arg count (unused)
 * @av: Arg vector (used for shell name in errors)
 * @env: Environment variables
 *
 * Return: 0
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t child_pid;
	char *token;
	char *argv[100]; /* Tableau pour stocker la commande et ses arguments */
	int i, status;

	(void)ac;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(0);
		}

		/* Découpage de la ligne en arguments */
		i = 0;
		token = strtok(line, " \t\n\r");
		while (token != NULL && i < 99)
		{
			argv[i] = token;
			token = strtok(NULL, " \t\n\r");
			i++;
		}
		argv[i] = NULL;

		if (argv[0] == NULL)
			continue;

		child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(argv[0], argv, env) == -1)
			{
				fprintf(stderr, "%s: 1: %s: not found\n", av[0], argv[0]);
				free(line);
				exit(127);
			}
		}
		else
			wait(&status);
	}
	free(line);
	return (0);
}
