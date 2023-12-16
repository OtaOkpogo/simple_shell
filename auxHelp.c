#include "simple_shell.h"

/**
 * auxHelpEnvir - The Help information for the builtinenv
 * Return: no return
 */
void auxHelpEnvir(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, _stringlen(help));
	help = "Print the environment of the shell.\n";
	write(STDOUT_FILENO, help, _stringlen(help));
}
/**
 * auxHelpSetenvir - Help info for the builtin setenv
 * Reurn: none
 */
void auxHelpSetenvir(void)
{
	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, _stringlen(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, _stringlen(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, _stringlen(help));
}
/**
 * auxHelpUnsetenvir - help info for builtin unsetenv
 * Return: none
 */
void auxHelpUnsetenvir(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, _stringlen(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, _stringlen(help));
}

/**
 * auxHelpGeneral - The Entry point for help info for d help builtin
 * Return: none
 */
void auxHelpGeneral(void)
{
	char *help = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, _stringlen(help));
	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, _stringlen(help));
	help = "Type 'help name' to find out more about the function 'name'.\n\n";
	write(STDOUT_FILENO, help, _stringlen(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, _stringlen(help));
	help = "[dir]\nexit: exit [n]\n env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, _stringlen(help));
	help = "[args]]\n setenv: setenv [variable] [value]\n unsetenv: ";
	write(STDOUT_FILENO, help, _stringlen(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, _stringlen(help));
}
/**
 * auxHelpExit - help info for the builint exit
 * Returb: none
 */
void auxHelpExit(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, _stringlen(help));
	help = "Exits the shell with a status of N. If N is ommitted, the exit";
	write(STDOUT_FILENO, help, _stringlen(help));
	help = "status is that of the last command executed\n";
	write(STDOUT_FILENO, help, _stringlen(help));
}
