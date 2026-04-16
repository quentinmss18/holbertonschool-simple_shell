#include "shell.h"

/**
 * found_in_path - handle found full path result
 * @cmd: command array
 * @full: malloc'ed full path (dir/cmd)
 * @dirs: splitted PATH (to free before returning)
 * Return: 1 if executable, -1 if found but not executable
 */
static int found_in_path(char **cmd, char *full, char **dirs)
{
	free_cmd(dirs);
	free(cmd[0]);
	cmd[0] = full;
	if (access(full, X_OK) != 0)
		return (-1);
	return (1);
}

/**
 * direct_path - helper to shorten get_path
 * @cmd: input
 * Return: 0 if not found, -1 if found but no x, 1 if f and x
 */
int direct_path(char **cmd)
{
	struct stat st;

	if (stat(cmd[0], &st) == 0 && S_ISDIR(st.st_mode)) /* if directory */
		return (-2);
	if (access(cmd[0], F_OK) != 0)
		return (0);
	if (access(cmd[0], X_OK) != 0)
		return (-1);
	return (1);
}

/**
 * get_path - replace cmd[0] with full path
 * @cmd: array from strtow (cmd[0] is the command name)
 * Description: Firstly retrieve env with getenv
 * check if we already have an absolute path
 * split path with strtow to create severals dirs
 * check access each dirs with the cmd concatenated to it
 * Return: 1 if a valid executable path is found, 0 otherwise
 */
int get_path(char **cmd)
{
	char *env, *path, *full = NULL;
	char **dirs;
	int i = 0;

	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
		return (0);
	if (cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/')
			|| (cmd[0][0] == '.' && cmd[0][1] == '.' &&
				cmd[0][2] == '/'))
		return (direct_path(cmd));
	env = _getenv("PATH");
	if (!env)
		return (0);
	path = _strdup(env + 5);
	if (!path)
		return (0);
	dirs = strtow(path);
	free(path);
	if (!dirs)
		return (0);
	while (dirs[i])
	{
		full = _calloc(sizeof(char), _strlen(dirs[i]) + _strlen(cmd[0]) + 2);
		if (!full)
			break;
		_strcat(full, dirs[i]);
		_strcat(full, "/");
		_strcat(full, cmd[0]);

		if (access(full, F_OK) == 0)
			return (found_in_path(cmd, full, dirs));
		free(full);
		full = NULL;
		i++;
	}
	free_cmd(dirs);
	return (0);
}
