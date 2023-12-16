#include "simple_shell.h"

/**
 * errorEnvir - error message for env in getEnvir
 * @data_sh: data relevant (count, arguments)
 * Return: error message
 */
char *errorEnvir(dataShell *data_sh)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = auxItoa(data_sh->count);
	msg = ":Unable to add/remove from environment\n";
	length = _stringlen(data_sh->argvec[0]) + _stringlen(ver_str);
	length += _stringlen(data_sh->args[0]) + _stringlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	_stringcpy(error, data_sh->argvec[0]);
	_stringcat(error, ": ");
	_stringcat(error, ver_str);
	_stringcat(error, ": ");
	_stringcat(error, data_sh->args[0]);
	_stringcat(error, msg);
	_stringcat(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * errorPath126 - The error message for path and failure denied permission
 * @data_sh: data relevant (count, arguments)
 *
 * Return: the error string
 */
char *errorPath126(dataShell *data_sh)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = auxItoa(data_sh->count);
	length = _stringlen(data_sh->argvec[0]) + _stringlen(ver_str);
	length += _stringlen(data_sh->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_stringcpy(error, data_sh->argvec[0]);
	_stringcat(error, ": ");
	_stringcat(error, ver_str);
	_stringcat(error, ": ");
	_stringcpy(error, data_sh->args[0]);
	_stringcpy(error, ": Permission denied\n");
	_stringcat(error, "\0");
	free(ver_str);
	return (error);
}
