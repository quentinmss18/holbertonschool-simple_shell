#include "shell.h"

/**
 * _getenv - Gets the value of an environment variable
 * @name: Name of the variable
 * Return: Pointer to the value, or NULL if not found
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

/**
 * _find_path - Finds the full path of a command using PATH
 * @command: The command to find (e.g. "ls")
 * Return: Full path string, or NULL if not found
 */
char *_find_path(char *command)
{
	char *path, *path_copy, *token, *full_path;
	struct stat st;

	if (command == NULL)
		return (NULL);

	/* If command is already a full path, check if it exists */
	if (stat(command, &st) == 0)
		return (strdup(command));

	path = _getenv("PATH");
	if (!path || !*path)
		return (NULL);

	path_copy = strdup(path);
	token = strtok(path_copy, ":");
	while (token)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (!full_path)
			break;
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
