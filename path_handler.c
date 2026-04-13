#include "shell.h"

/**
 * _find_path - Cherche si une commande existe dans les dossiers du PATH
 * @command: Nom de la commande (ex: "ls")
 * Return: Chemin complet si trouvé, sinon NULL
 */
char *_find_path(char *command)
{
	char *path, *path_copy, *token, *full_path;
	struct stat st;

	if (stat(command, &st) == 0)
		return (strdup(command));

	path = _getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	token = strtok(path_copy, ":");
	while (token)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		sprintf(full_path, "%s/%s", token, command);
		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * _getenv - Récupère une variable d'environnement
 * @name: Nom de la variable (ex: "PATH")
 * Return: Valeur de la variable ou NULL
 */
char *_getenv(const char *name)
{
	int i = 0;
	size_t len = strlen(name);

	while (environ[i])
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}
