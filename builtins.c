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
	return (0);
}
