#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/**
 * main - Simple shell core logic
 * @ac: Argument count
 * @av: Argument vector
 * @env: Environment variables
 *
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t child_pid;
	char *argv[] = {NULL, NULL};

	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		read = getline(&line, &len, stdin);
		if (read == -1) /* Gestion du Ctrl+D (EOF) */
		{
			free(line);
			exit(EXIT_SUCCESS);
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		argv[0] = line;
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
		}
		else if (child_pid == 0) /* Processus enfant */
		{
			if (execve(argv[0], argv, env) == -1)
			{
				perror(av[0]);
				free(line);
				exit(EXIT_FAILURE);
			}
		}
		else /* Processus parent */
		{
			wait(NULL);
		}
	}
	free(line);
	return (0);
}
