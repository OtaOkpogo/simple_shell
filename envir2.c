#include "simple_shell.h"

/**
 * copyInfo - To copy info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *copyInfo(char *name, char *value)
{
	char *new;
	int lenName, lenValue, len;

	lenName = _stringlen(name);
	lenValue = _stringlen(value);
	len = lenName + lenValue + 2;
	new = malloc(sizeof(char) * (len));
	_stringcpy(new, name);
	_stringcat(new, "=");
	_stringcat(new, value);
	_stringcat(new, "\0");

	return (new);
}

/**
 * setEnvir- To set an environment variable
 *
 * @name: The name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: no return
 */
void setEnvir(char *name, char *value, dataShell *datash)
{
	int a;
	char *varEnv, *nameEnv;

	for (a = 0; datash->envir[a]; a++)
	{
		varEnv = _stringdup(datash->envir[a]);
		nameEnv = _stringtok(varEnv, "=");
		if (_stringcmp(nameEnv, name) == 0)
		{
			free(datash->envir[a]);
			datash->envir[a] = copyInfo(nameEnv, value);
			free(varEnv);
			return;
		}
		free(varEnv);
	}

	datash->envir = _reallocatedp(datash->envir, a, sizeof(char *) * (a + 2));
	datash->envir[a] = copyInfo(name, value);
	datash->envir[a + 1] = NULL;
}

/**
 * _setEnvir - To compare env variables names
 * with the name passed.
 * @datash:  relevant data (env name and env value)
 *
 * Return: 1 on success.
 */
int _setEnvir(dataShell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		getError(datash, -1);
		return (1);
	}

	setEnvir(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetEnvir - To delete a environment variable
 *
 * @datash: relevant data(env name)
 *
 * Return: 1 on success.
 */
int _unsetEnvir(dataShell *datash)
{
	char **reallocateEnvir;
	char *varEnv, *nameEnv;
	int i, p, k;

	if (datash->args[1] == NULL)
	{
		getError(datash, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datash->envir[i]; i++)
	{
		varEnv = _stringdup(datash->envir[i]);
		nameEnv = _stringtok(varEnv, "=");
		if (_stringcmp(nameEnv, datash->args[1]) == 0)
		{
			k = i;
		}
		free(varEnv);
	}
	if (k == -1)
	{
		getError(datash, -1);
		return (1);
	}
	reallocateEnvir = malloc(sizeof(char *) * (i));
	for (i = p = 0; datash->envir[i]; i++)
	{
		if (i != k)
		{
			reallocateEnvir[p] = datash->envir[i];
			p++;
		}
	}
	reallocateEnvir[p] = NULL;
	free(datash->envir[k]);
	free(datash->envir);
	datash->envir = reallocateEnvir;
	return (1);
}
