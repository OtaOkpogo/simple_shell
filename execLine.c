#include "simple_shell.h"

/**
 * execLine - finds builtins and commands
 *
 * @datash: relevant data (args)
 * Return: 1 on success.
 */
int execLine(dataShell *datash)
{
	int (*builtin)(dataShell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = getBuiltin(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (cmdExec(datash));
}
