#include "simple_shell.h"

/**
 * bringLine - To assign the line var for get_line
 * @line_ptr: Buffer that store the input str
 * @buffer: The str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */
void bringLine(char **line_ptr, size_t *n, char *buffer, size_t j)
{

	if (*line_ptr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*line_ptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*line_ptr = buffer;
	}
	else
	{
		_stringcpy(*line_ptr, buffer);
		free(buffer);
	}
}
/**
 * getLine - To read inpt from stream
 * @line_ptr: The buffer that stores the input
 * @n: size of lineptr
 * @stream: The stream to read from
 * Return: The number of bytes
 */
ssize_t getLine(char **line_ptr, size_t *n, FILE *stream)
{
	int a;
	static ssize_t inp;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (inp == 0)
		fflush(stream);
	else
		return (-1);
	inp = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		a = read(STDIN_FILENO, &t, 1);
		if (a == -1 || (a == 0 && inp == 0))
		{
			free(buffer);
			return (-1);
		}
		if (a == 0 && inp != 0)
		{
			inp++;
			break;
		}
		if (inp >= BUFSIZE)
			buffer = _reallocate(buffer, inp, inp + 1);
		buffer[inp] = t;
		inp++;
	}
	buffer[inp] = '\0';
	bringLine(line_ptr, n, buffer, inp);
	retval = inp;
	if (a != 0)
		inp = 0;
	return (retval);
}
