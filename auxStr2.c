#include "simple_shell.h"
/**
 * _stringdup - duplicates a str in d heap memo
 * @s: type char pointer str
 * Return: duplicated str
 */
char *_stringdup(const char *s)
{
	char *new;
	size_t len;

	len = _stringlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcopy(new, s, len + 1);
	return (new);
}

/**
 * _stringlen - returns d lenght of a str
 * @s: type char pointer
 * Return: 0
 */
int _stringlen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}
/**
 * cmpChars - compare chars of str
 * @str: input string
 * @delim: delimiter
 * Return: 1 or 0
 */
int cmpChars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _stringtok - splits a str by some delimiter
 * @str: input str
 * @delim: delimiter
 * Return: str splited
 */
char *_stringtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (cmpChars(str, delim))
			return (NULL);
		splitted = str; /*Store first address*/
		i = _stringlen(str);
		str_end = &str[i]; /*store last address*/
	}
	str_start = splitted;
	if (str_start == str_end) /* reaching d emd */
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/* breaking loop finding d next token */
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/* replacing delimiter for null char */
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';

				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /* str != delim */
			bool = 1;
	}
	if (bool == 0) /*str == delim*/
		return (NULL);
	return (str_start);
}
/**
 * _is_digit - defines if str passed is a numb
 * @s: str
 * Return: 1 if str is a num, 0 if not
 */
int _is_digit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
