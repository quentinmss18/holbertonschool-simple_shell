#include "shell.h"

/**
 * free_args - Frees a null-terminated array of strings
 * @args: The array to free
 */
void free_args(char **args)
{
	int i = 0;

	if (!args)
		return;

	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/**
 * is_empty - Checks if a string is empty or whitespace only
 * @line: The string to check
 *
 * Return: 1 if empty/whitespace, 0 otherwise
 */
int is_empty(char *line)
{
	int i = 0;

	if (!line)
		return (1);

	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' &&
		    line[i] != '\r' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
