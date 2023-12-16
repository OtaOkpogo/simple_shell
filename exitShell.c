#include "simple_shell.h"

/**
 * exitShell - To exit the shell
 *
 * @datash: relevant data (status and args)
 * Return: 0 on success.
 */
int exitShell(dataShell *datash)
{
	unsigned int u_status;
	int isDigit;
	int string_len;
	int big_num;

	if (datash->args[1] != NULL)
	{
		u_status = _atoi(datash->args[1]);
		isDigit = _is_digit(datash->args[1]);
		string_len = _stringlen(datash->args[1]);
		big_num = u_status > (unsigned int)INT_MAX;
		if (!isDigit || string_len > 10 || big_num)
		{
			getError(datash, 2);
			datash->stats = 2;
			return (1);
		}
		datash->stats = (u_status % 256);
	}
	return (0);
}
