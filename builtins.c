#include "shell.h"

/**
 * builtin_exit - Exits the shell cleanly
 * @args: Argument array (unused beyond args[0])
 *
 * Does not return.
 */
static void builtin_exit(char **args)
{
	(void)args;
	exit(EXIT_SUCCESS);
}

/**
 * builtin_env - Prints each environment variable on its own line
 * @args: Argument array (unused)
 */
static void builtin_env(char **args)
{
	int i;

	(void)args;
	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * handle_builtin - Checks if a command is a built-in and runs it
 * @args: Null-terminated array of arguments; args[0] is the command name
 *
 * Return: 1 if a built-in was matched and executed, 0 otherwise
 */
int handle_builtin(char **args)
{
	if (strcmp(args[0], "exit") == 0)
	{
		builtin_exit(args);
		return (1); /* never reached, but satisfies compiler */
	}
	if (strcmp(args[0], "env") == 0)
	{
		builtin_env(args);
		return (1);
	}
	return (0);
}
