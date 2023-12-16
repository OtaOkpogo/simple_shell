#include "simple_shell.h"

/**
 * auxHelp - The help info for the builtin help
 * Return: none
 */
void auxHelp(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _stringlen(help));
	help = "\tDisplay information about builtin commands.\n";
	write(STDOUT_FILENO, help, _stringlen(help));
	help = "Displays brief summaries of builtin commands.\n ";
	write(STDOUT_FILENO, help, _stringlen(help));
}

/**
 * auxHelpAlias - Help info for the builtin alias
 * Return: none
 */
void auxHelpAlias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _stringlen(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _stringlen(help));
}

/**
 * auxHelpCdir - Help info for the builtin alias
 * Return: none
 */
void auxHelpCdir(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [ -@]] [dir]\n";

	write(STDOUT_FILENO, help, _stringlen(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _stringlen(help));
}
