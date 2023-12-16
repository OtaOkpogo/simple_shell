#include "simple_shell.h"

/**
 * swapChar - To swap | and & for non-printed chars
 *
 * @inp: input string
 * @bool: a type of swap
 * Return: swapped string
 */
char *swapChar(char *inp, int bool)
{
	int a;

	if (bool == 0)
	{
		for (a = 0; inp[a]; a++)
		{
			if (inp[a] == '|')
			{
				if (inp[a + 1] != '|')
					inp[a] = 16;
				else
					a++;
			}

			if (inp[a] == '&')
			{
				if (inp[a + 1] != '&')
					inp[a] = 12;
				else
					a++;
			}
		}
	}
	else
	{
		for (a = 0; inp[a]; a++)
		{
			inp[a] = (inp[a] == 16 ? '|' : inp[a]);
			inp[a] = (inp[a] == 12 ? '&' : inp[a]);
		}
	}
	return (inp);
}

/**
 * addNodes - To add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @inp: input string
 * Return: no return
 */
void addNodes(seppList **head_s, lineeList **head_l, char *inp)
{
	int a;
	char *line;

	inp = swapChar(inp, 0);

	for (a = 0; inp[a]; a++)
	{
		if (inp[a] == ';')
			addSepNodeEnd(head_s, inp[a]);

		if (inp[a] == '|' || inp[a] == '&')
		{
			addSepNodeEnd(head_s, inp[a]);
			a++;
		}
	}

	line = _stringtok(inp, ";|&");
	do {
		line = swapChar(line, 1);
		addLineNodeEnd(head_l, line);
		line = _stringtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * goNext - To go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @datash: data structure
 * Return: no return
 */
void goNext(seppList **list_s, lineeList **list_l, dataShell *datash)
{
	int loop_sep;
	seppList *ls_s;
	lineeList *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->stats == 0)
		{
			if (ls_s->septor == '&' || ls_s->septor == ';')
				loop_sep = 0;
			if (ls_s->septor == '|')
				ls_l = ls_l->nextNode, ls_s = ls_s->nextNode;
		}
		else
		{
			if (ls_s->septor == '|' || ls_s->septor == ';')
				loop_sep = 0;
			if (ls_s->septor == '&')
				ls_l = ls_l->nextNode, ls_s = ls_s->nextNode;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->nextNode;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * splitCommands - To split command lines according to
 * the separators ;, | and &, and executes them
 *
 * @datash: data structure
 * @inp: input string
 * Return: 0 to exit, 1 to continue
 */
int splitCommands(dataShell *datash, char *inp)
{

	seppList *head_s, *list_s;
	lineeList *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	addNodes(&head_s, &head_l, inp);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->inp = list_l->cmline;
		datash->args = splitLine(datash->inp);
		loop = execLine(datash);
		free(datash->args);

		if (loop == 0)
			break;

		goNext(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->nextNode;
	}

	freeSepList(&head_s);
	freeLineList(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * splitLine - To tokenize the input string
 *
 * @inp: input string.
 * Return: string splitted.
 */
char **splitLine(char *inp)
{
	size_t bsize;
	size_t j;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _stringtok(inp, TOK_DELIM);
	tokens[0] = token;

	for (j = 1; token != NULL; j++)
	{
		if (j == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocatedp(tokens, j, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _stringtok(NULL, TOK_DELIM);
		tokens[j] = token;
	}

	return (tokens);
}
