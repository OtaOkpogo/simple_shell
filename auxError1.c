#include "simple_shell.h"

/**
 * stringcatCdir - function that concatenates the message for cdir error
 *
 * @datash: relevant data
 * @msg: The message to print
 * @error: output message
 * @ver_str: counter lines
 * Description - it prints an error message
 * Return: error message
 */
char *stringcatCdir(dataShell *datash, char *msg, char *error, char *ver_str)
{
	char *illegalFlag;

	_stringcpy(error, datash->argvec[0]);
	_stringcat(error, ": ");
	_stringcat(error, ver_str);
	_stringcat(error, ": ");
	_stringcat(error, datash->args[0]);
	_stringcat(error, msg);
	if (datash->args[1][0] == '-')
	{
		illegalFlag = malloc(3);
		illegalFlag[0] = '-';
		illegalFlag[1] = datash->args[1][1];
		illegalFlag[2] = '\0';
		_stringcat(error, illegalFlag);
		free(illegalFlag);
	}
	else
	{
		_stringcat(error, datash->args[1]);
	}

	_stringcat(error, "\n");
	_stringcat(error, "\0");
	return (error);
}

/**
 * errorGetCdir - error message for cdir command in get_cdir
 * @datash: relevant data (directory)
 * Description - it prints an error message for cdir
 * Return: Error message
 */
char *errorGetCdir(dataShell *datash)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = auxItoa(datash->count);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _stringlen(datash->args[1]);
	}

	length = _stringlen(datash->argvec[0]) + _stringlen(datash->args[0]);
	length += _stringlen(ver_str) + _stringlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = stringcatCdir(datash, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * errorNotFound - The generic error message for command not found
 * @datash: relevant data (counter, arguments)
 * Description - it prints an error message for command not found
 * Return: Error message
 */
char *errorNotFound(dataShell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = auxItoa(datash->count);
	length = _stringlen(datash->argvec[0]) + _stringlen(ver_str);
	length += _stringlen(datash->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_stringcpy(error, datash->argvec[0]);
	_stringcat(error, ": ");
	_stringcat(error, ver_str);
	_stringcat(error, ": ");
	_stringcat(error, datash->args[0]);
	_stringcat(error, ": not found\n");
	_stringcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * errorExitShell - The generic error message for exit in getExit
 * @datash: data relevant (counter, arguments)
 * Description - to print error message for exit in getExit
 *
 * Return: Error message
 */
char *errorExitShell(dataShell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = auxItoa(datash->count);
	length = _stringlen(datash->argvec[0]) + _stringlen(ver_str);
	length += _stringlen(datash->args[0]) + _stringlen(datash->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_stringcpy(error, datash->argvec[0]);
	_stringcat(error, ": ");
	_stringcat(error, ver_str);
	_stringcat(error, ": ");
	_stringcat(error, datash->args[0]);
	_stringcat(error, ": Illegal number: ");
	_stringcat(error, datash->args[1]);
	_stringcat(error, "\n\0");
	free(ver_str);

	return (error);
}
