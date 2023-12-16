#include "simple_shell.h"

/**
 * isCdir - checks ":" if is in the current dir
 * @path: type char pointer char
 * @i: type int pointer of index
 * Return: 1 if d path is searchable in the cd, 0 if not
 */
int isCdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;
	return (0);
}

/**
 * _which - locates a command
 *
 * @cmd: command name
 * @_envir: environment variable
 * Return: location of the command
 */
char *_which(char *cmd, char **_envir)
{
	char *path, *ptr_path, *token_path, *dir;

	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenvir("PATH", _envir);
	if (path)
	{
		ptr_path = _stringdup(path);
		len_cmd = _stringlen(cmd);
		token_path = _stringtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (isCdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _stringlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_stringcpy(dir, token_path);
			_stringcat(dir, "/");
			_stringcat(dir, cmd);
			_stringcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _stringtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * isExecutable - determines if its an executable
 * @data_sh: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int isExecutable(dataShell *data_sh)
{
	struct stat st;
	int i;
	char *inp;

	inp = data_sh->args[0];
	for (i = 0; inp[i]; i++)
	{
		if (inp[i] == '.')
		{
			if (inp[i + 1] == '.')
				return (0);
			if (inp[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (inp[i] == '/' && i != 0)

		{
			if (inp[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(inp + i, &st) == 0)
	{
		return (i);
	}
	getError(data_sh, 127);
	return (-1);
}

/**
 * checkErrorCmd - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @data_sh: data structure
 * Return: 1 if there is an error, 0 if not
 */
int checkErrorCmd(char *dir, dataShell *data_sh)
{
	if (dir == NULL)
	{
		getError(data_sh, 127);
		return (1);
	}

	if (_stringcmp(data_sh->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			getError(data_sh, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(data_sh->args[0], X_OK) == -1)
		{
			getError(data_sh, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmdExec - executes command lines
 *
 * @data_sh: data relevant (args & inp)
 * Return: 1 on success
 */
int cmdExec(dataShell *data_sh)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = isExecutable(data_sh);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(data_sh->args[0], data_sh->envir);
		if (checkErrorCmd(dir, data_sh) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(data_sh->args[0], data_sh->envir);
		else
			dir = data_sh->args[0];
		execve(dir + exec, data_sh->args, data_sh->envir);
	}
	else if (pd < 0)
	{
		perror(data_sh->argvec[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	data_sh->stats = state / 256;
	return (1);
}
