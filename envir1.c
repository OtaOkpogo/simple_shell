#include "simple_shell.h"
/**
 * cmp_env_name - compares env variables names
 * with d name passed
 * @nenv: name of d environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}
/**
 * _getenvir - get an environment variable
 * @name: name of d environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found
 * In other case, returns NULL
 */
char *_getenvir(const char *name, char **_environ)
{
	char *ptr_env;
	int i, mov;

	/* initialize ptr_envir value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; _environ[i]; i++)
	{
		/* If name & envir are equal */
		mov = cmp_env_name(_environ[i], name);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _envir - prints d environment variables
 *
 * @data_sh: data relevant
 * Return: 1 on success
 */
int _envir(dataShell *data_sh)
{
	int i, j;

	for (i = 0; data_sh->envir[i]; i++)
	{
		for (j = 0; data_sh->envir[i][j]; j++)
			;

		write(STDOUT_FILENO, data_sh->envir[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	data_sh->stats = 0;

	return (1);
}
