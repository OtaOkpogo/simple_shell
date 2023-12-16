#include "simple_shell.h"

/**
 * getBuiltin - Builtin that pais the command in the arg
 * @cmd: command
 * Return: a function pointer of the builtin command
 */
int (*getBuiltin(char *cmd))(dataShell *)
{
	builtin_t builtin[] = {
		{ "env", _envir },
		{ "exit", exitShell },
		{ "setenv", _setEnvir },
		{ "unsetenv", _unsetEnvir },
		{ "cd", cdShell },
		{ "help", getHelp },
		{ NULL, NULL }
	};
	int k;

	for (k = 0; builtin[k].cmname; k++)
	{
		if (_stringcmp(builtin[k].cmname, cmd) == 0)
			break;
	}

	return (builtin[k].df);
}
