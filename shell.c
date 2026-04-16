#include "shell.h"

/**
 * read_line - Reads a line from standard input
 * @eof: Pointer to EOF flag, set to 1 on EOF
 *
 * Return: Pointer to the line read, or NULL on empty/error
 */
char *read_line(int *eof)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t chars_read;

	*eof = 0;
	chars_read = getline(&line, &bufsize, stdin);
	if (chars_read == -1)
	{
		*eof = 1;
		return (line);
	}

	/* Remove trailing newline */
	if (line[chars_read - 1] == '\n')
		line[chars_read - 1] = '\0';

	return (line);
}

/**
 * split_line - Tokenizes a line into an array of arguments
 * @line: The input line to split
 *
 * Return: Null-terminated array of strings, or NULL on failure
 */
char **split_line(char *line)
{
	char **args = NULL;
	char *token = NULL;
	int count = 0, i = 0;
	char *line_copy = NULL;
	char *tmp = NULL;

	/* Count tokens first */
	line_copy = strdup(line);
	if (!line_copy)
		return (NULL);

	token = strtok(line_copy, " \t\r\n");
	while (token)
	{
		count++;
		token = strtok(NULL, " \t\r\n");
	}
	free(line_copy);

	if (count == 0)
		return (NULL);

	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);

	tmp = strdup(line);
	if (!tmp)
	{
		free(args);
		return (NULL);
	}

	token = strtok(tmp, " \t\r\n");
	while (token)
	{
		args[i] = strdup(token);
		if (!args[i])
		{
			for (; i >= 0; i--)
				free(args[i]);
			free(args);
			free(tmp);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " \t\r\n");
	}
	args[i] = NULL;
	free(tmp);

	return (args);
}

/**
 * execute - Forks and executes a command
 * @args: Array of arguments (args[0] is the command)
 * @prog_name: Name of the shell program (for error messages)
 *
 * Return: Exit status of the child process
 */
int execute(char **args, char *prog_name)
{
	pid_t pid;
	int status;
	char *cmd = NULL;
	static int cmd_num = 1;

	/* Check if command contains a '/' (absolute or relative path) */
	if (strchr(args[0], '/'))
		cmd = args[0];
	else
		cmd = find_in_path(args[0]);

	if (!cmd)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, cmd_num++, args[0]);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (cmd != args[0])
			free(cmd);
		return (-1);
	}

	if (pid == 0)
	{
		/* Child process */
		if (execve(cmd, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				prog_name, cmd_num, args[0]);
			if (cmd != args[0])
				free(cmd);
			exit(127);
		}
	}
	else
	{
		/* Parent process */
		waitpid(pid, &status, 0);
		cmd_num++;
	}

	if (cmd != args[0])
		free(cmd);

	return (status);
}
