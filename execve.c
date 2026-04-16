#include "shell.h"
#include <errno.h>

/**
 * execve_cmd - use execve to process the command
 * @cmd: input forming an array of commands
 * @prog: prog name av[0] for error messages
 * @line: line number for error messages
 * Description: This code firstly uses fork to create a child
 * if the fork is successfull execve tries to run the command
 * Return: None
 **/

int execve_cmd(char **cmd, char *prog, unsigned int line)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		execve(cmd[0], cmd, environ);
		if (errno == EACCES)
		{
			print_perm_denied(prog, line, cmd[0]);
			exit(126);
		}
		if (errno == EISDIR)
		{
			print_is_dir(prog, line, cmd[0]);
			exit(126);
		}
		print_not_found(prog, line, cmd[0]);
		exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status)); /*return child process exit code */
	return (1);
}
