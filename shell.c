#include "shell.h"

/**
 * main - Entry point for the simple shell 0.3
 * @ac: Argument count (unused)
 * @av: Argument vector
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	char *line = NULL, *path = NULL;
	size_t len = 0;
	ssize_t nread;
	char *args[2];
	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);

		nread = getline(&line, &len, stdin);
		if (nread == -1) /* Handle EOF (Ctrl+D) */
			break;

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (strlen(line) == 0)
			continue;

		args[0] = line;
		args[1] = NULL;
		path = _find_path(args[0]);

		if (path)
		{
			if (fork() == 0)
			{
				if (execve(path, args, environ) == -1)
					perror(av[0]);
				exit(EXIT_FAILURE);
			}
			wait(NULL);
			free(path);
		}
		else
			fprintf(stderr, "%s: 1: %s: not found\n", av[0], line);
	}
	free(line);
	return (0);
}
