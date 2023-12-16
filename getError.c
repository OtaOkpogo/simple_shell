#include "simple_shell.h"

/**
 * getError - To call the error according the builtin, syntax or permission
 * @datash: The data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int getError(dataShell *datash, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = errorEnvir(datash);
		break;
	case 126:
		error = errorPath126(datash);
		break;
	case 127:
		error = errorNotFound(datash);
		break;
	case 2:
		if (_stringcmp("exit", datash->args[0]) == 0)
			error = errorExitShell(datash);
		else if (_stringcmp("cd", datash->args[0]) == 0)
			error = errorGetCdir(datash);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _stringlen(error));
		free(error);
	}

	datash->stats = eval;
	return (eval);
}
