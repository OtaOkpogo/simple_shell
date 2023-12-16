#include "simple_shell.h"
/**
 * cdShell - changes current dir
 * @data_sh: data relevant
 * Return: 1 on success
 */
int cdShell(dataShell *data_sh)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = data_sh->args[1];

	if (dir != NULL)
	{
		ishome = _stringcmp("$HOME", dir);
		ishome2 = _stringcmp("~", dir);
		isddash = _stringcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cdirToHome(data_sh);
		return (1);
	}

	if (_stringcmp("-", dir) == 0)
	{
		cdirPrev(data_sh);
		return (1);
	}

	if (_stringcmp(".", dir) == 0 || _stringcmp("..", dir) == 0)
	{
		cdirDot(data_sh);
		return (1);
	}
	cdirTo(data_sh);

	return (1);
}
