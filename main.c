#include "shell.h"

/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	char **args = NULL;
	int eof = 0;
	char *prog_name = "hsh";

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);

		line = read_line(&eof);
		if (eof)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			break;
		}
		if (!line)
			continue;
		if (is_empty(line))
		{
			free(line);
			continue;
		}

		args = split_line(line);
		free(line);
		if (!args || !args[0])
		{
			free_args(args);
			continue;
		}

		execute(args, prog_name);
		free_args(args);
	}

	return (0);
}
