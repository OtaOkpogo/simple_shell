#include "simple_shell.h"

/**
 * readLine - To read the input string.
 *
 * @i_eof: returns the value of getline function
 * Return: input string
 */
char *readLine(int *i_eof)
{
	char *inp = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&inp, &bufsize, stdin);

	return (inp);
}
