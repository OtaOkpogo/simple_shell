#include "simple_shell.h"
/**
 * repeatedChar - To count repetitions of a char
 * @inp: input string
 * @i: index
 * Return: repetitions
 */
int repeatedChar(char *inp, int i)
{
	if (*(inp - 1) == *inp)
		return (repeatedChar(inp - 1, i + 1));

	return (i);
}
/**
 * errorSepOp - finds syntax errors
 * @inp: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int errorSepOp(char *inp, int i, char last)
{
	int count;

	count = 0;
	if (*inp == '\0')
		return (0);

	if (*inp == ' ' || *inp == '\t')
		return (errorSepOp(inp + 1, i + 1, last));

	if (*inp == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*inp == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = repeatedChar(inp, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*inp == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = repeatedChar(inp, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (errorSepOp(inp + 1, i + 1, *inp));
}

/**
 * firstChar - finds index of 1st char
 * @inp: input string
 * @i: index
 * Return: 1 if there is an error, 0 if not
 */
int firstChar(char *inp, int *i)
{
	for (*i = 0; inp[*i]; *i += 1)
	{
		if (inp[*i] == ' ' || inp[*i] == '\t')
			continue;

		if (inp[*i] == ';' || inp[*i] == '|' || inp[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * printSyntaxError - prints when a syntax error
 * @data_sh: data structure
 * @inp: input string
 * @i: index of the error
 * @bool: to controk msg error
 * Return: no return
 */
void printSyntaxError(dataShell *data_sh, char *inp, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *count;
	int length;

	if (inp[i] == ';')
	{
		if (bool == 0)
			msg = (inp[i + 1] == ';' ? ";;" : ";");
		else
			msg = (inp[i + 1] == ';' ? ";;" : ";");
	}

	if (inp[i] == '|')
		msg = (inp[i + 1] == '|' ? "||" : "|");
	if (inp[i] == '&')
		msg = (inp[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	count = auxItoa(data_sh->count);
	length = _stringlen(data_sh->argvec[0]) + _stringlen(count);
	length += _stringlen(msg) + _stringlen(msg2) + _stringlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(count);
		return;
	}
	_stringcpy(error, data_sh->argvec[0]);
	_stringcat(error, ": ");
	_stringcat(error, count);
	_stringcat(error, msg2);
	_stringcat(error, msg);
	_stringcat(error, msg3);
	_stringcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(count);
}
/**
 * checkSyntaxError - intermediate function 2
 * find & print a syntax error
 * @data_sh: data structure
 * @inp: inp string
 * Return: 1 if there is an error, 0 if not
 */
int checkSyntaxError(dataShell *data_sh, char *inp)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = firstChar(inp, &begin);
	if (f_char == -1)
	{
		printSyntaxError(data_sh, inp, begin, 0);
		return (1);
	}
	i = errorSepOp(inp + begin, 0, *(inp + begin));
	if (i != 0)
	{
		printSyntaxError(data_sh, inp, begin + 1, 1);
		return (1);
	}

	return (0);
}
