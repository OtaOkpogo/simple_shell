#include "simple_shell.h"

/**
 * _stringcat - concatenate 2 str
 * @dest: char pointer d dest of d copied str
 * @src: const char pointer d source of str
 * Return: dest
 */
char *_stringcat(char *dest, const char *src)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}
/**
 * _stringcpy - copies d str pointed to btmy src
 * @dest: type char pointer d dest of d copied str
 * @src: tyoe char pointr d source of str
 * Return: dest
 */
char *_stringcpy(char *dest, char *src)
{
	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}
	dest[a] = '\0';

	return (dest);
}
/**
 * _stringcmp - func dt compares 2 str
 * @s1: type str compared
 * @s2: type str compared
 * Return: always 0
 */
int _stringcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;

	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}
/**
 * _stringchr - locates a char in a str
 * @s: string
 * @c: char
 * Return: pointer to d first occurrence of c charcter
 */
char *_stringchr(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}
 /**
  * _stringspn - gets the length of a prefix substring
  * @s: initial segment
  * @accept: accepted bytes
  * Return: no of accepted bytes
  * function _stringspn: gets length
  */
int _stringspn(char *s, char *accept)
{
	int i, j, bool;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + i) == *(accept + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}
