#include "simple_shell.h"

/**
 * getHelp - A function that retrieves help messages according builtin
 * @datash: data structure (args and input)
 * Return: Return 0
*/
int getHelp(dataShell *datash)
{

	if (datash->args[1] == 0)
		auxHelpGeneral();
	else if (_stringcmp(datash->args[1], "setenv") == 0)
		auxHelpSetenvir();
	else if (_stringcmp(datash->args[1], "env") == 0)
		auxHelpEnvir();
	else if (_stringcmp(datash->args[1], "unsetenv") == 0)
		auxHelpUnsetenvir();
	else if (_stringcmp(datash->args[1], "help") == 0)
		auxHelp();
	else if (_stringcmp(datash->args[1], "exit") == 0)
		auxHelpExit();
	else if (_stringcmp(datash->args[1], "cd") == 0)
		auxHelpCdir();
	else if (_stringcmp(datash->args[1], "alias") == 0)
		auxHelpAlias();
	else
		write(STDERR_FILENO, datash->args[0],
		      _stringlen(datash->args[0]));

	datash->stats = 0;
	return (1);
}
