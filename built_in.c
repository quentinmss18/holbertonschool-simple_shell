#include "shell.h"

/**
 * env_builtin - handle env built in
 * @cmd: cmd input
 * Description: check if there is only 1 argument
 * if this argument is "env" print the env from
 * the environ extern char in header
 * Return: 1 if success else 0
 */
int env_builtin(char **cmd)
{
	int i = 0;
	int j = 0;

	if (cmd == NULL || cmd[0] == NULL)
		return (0);
	if (_strcmp(cmd[0], "env") == 0 && cmd[1] == NULL)
	{
		while (environ[i])
		{
			j = 0;
			while (environ[i][j])
			{
				_putchar(environ[i][j]);
				j++;
			}
			if (environ[i + 1] != NULL)
				_putchar('\n');
			i++;
		}
		return (1);
	}
	return (0);
}

/**
 * exit_builtin - handle the exit built in with status
 * @cmd: input
 * @prog: av[0]
 * @line: line
 * Description: check for the first 2 arguments
 * if only 1 argument that is "exit" just exit
 * if "exit" followed by a number argument exit
 * with status % 256 to match unix 8 bits return
 * Return: 0 if not valid exit or else just exit
 */
int exit_builtin(char **cmd, char *prog, unsigned int line)
{
	int status = 0;

	if (!cmd || !cmd[0])
		return (0);
	if (_strcmp(cmd[0], "exit") != 0)
		return (0);
	if (!cmd[1])
	{
		free_cmd(cmd);
		exit(status);
	}
	/*cas d'erreurs: argument non-nombre/nombre negatif exit2 */
	if (!_isnumber(cmd[1]))
	{
		print_exit_illegal(prog, line, cmd[1]);
		free_cmd(cmd);
		exit(2);
	}
	if (cmd[1] != NULL && cmd[2] != NULL)
	{
		print_exit_too_many(prog, line);
		return (1);
	}
	status = _atoi(cmd[1]) % 256; /*8bits unix like*/
	if (status < 0)
		status += 256;
	free_cmd(cmd);
	exit(status);
	return (0);
}
