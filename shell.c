#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Point d'entrée du shell simple
 * @ac: Nombre d'arguments (non utilisé)
 * @av: Tableau des arguments (utilisé pour le nom du programme)
 * @env: Environnement système
 *
 * Return: Toujours 0
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t child_pid;
	char *argv[2];
	int status;

	(void)ac;

	while (1)
	{
		/* Affiche le prompt uniquement en mode interactif */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		nread = getline(&line, &len, stdin);
		if (nread == -1) /* Gestion de Ctrl+D */
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(EXIT_SUCCESS);
		}

		/* Extraction de la commande sans espaces/newlines */
		argv[0] = strtok(line, " \t\n\r");
		argv[1] = NULL;

		/* Si la ligne est vide, on ignore */
		if (argv[0] == NULL)
			continue;

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
		}
		else if (child_pid == 0)
		{
			/* Exécution du programme */
			if (execve(argv[0], argv, env) == -1)
			{
				/* Format d'erreur identique à sh */
				fprintf(stderr, "%s: 1: %s: not found\n", av[0], argv[0]);
				free(line);
				exit(127);
			}
		}
		else
		{
			wait(&status);
		}
	}
	free(line);
	return (0);
}
