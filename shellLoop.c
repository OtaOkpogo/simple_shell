#include "simple_shell.h"

/**
 * withoutComment - To delete comments from the input
 *
 * @inp: input string
 * Return: input without comments
 */
char *withoutComment(char *inp)
{
	int j, up_to;

	up_to = 0;
	for (j = 0; inp[j]; j++)
	{
		if (inp[j] == '#')
		{
			if (j == 0)
			{
				free(inp);
				return (NULL);
			}

			if (inp[j - 1] == ' ' || inp[j - 1] == '\t' || inp[j - 1] == ';')
				up_to = j;
		}
	}

	if (up_to != 0)
	{
		inp = _reallocate(inp, j, up_to + 1);
		inp[up_to] = '\0';
	}

	return (inp);
}

/**
 * shellLoop - a Loop of shell
 * @datash: relevant  data(av, input, args)
 *
 * Return: no return.
 */
void shellLoop(dataShell *datash)
{
	int loop, j_eof;
	char *inp;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		inp = readLine(&j_eof);
		if (j_eof != -1)
		{
			inp = withoutComment(inp);
			if (inp == NULL)
				continue;

			if (checkSyntaxError(datash, inp) == 1)
			{
				datash->stats = 2;
				free(inp);
				continue;
			}
			inp = repVar(inp, datash);
			loop = splitCommands(datash, inp);
			datash->count += 1;
			free(inp);
		}
		else
		{
			loop = 0;
			free(inp);
		}
	}
}
