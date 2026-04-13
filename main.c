#include "shell.h"

/**
 * main - Simple shell 0.3
 * @ac: Nombre d'arguments (inutilisé)
 * @av: Tableau d'arguments
 * Return: 0 en succès
 */
int main(int ac, char **av)
{
	char *line = NULL, *path = NULL;
	size_t len = 0;
	ssize_t read;
	char *args[2];
	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf(":) ");
		read = getline(&line, &len, stdin);
		if (read == -1)
			break;
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		args[0] = line;
		args[1] = NULL;
		path = _find_path(args[0]);

		if (path)
		{
			if (fork() == 0)
			{
				if (execve(path, args, environ) == -1)
					perror(av[0]);
			}
			else
				wait(NULL);
			free(path);
		}
		else
			fprintf(stderr, "%s: 1: %s: not found\n", av[0], line);
	}
	free(line);
	return (0);
}
