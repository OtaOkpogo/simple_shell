#include "simple_shell.h"

/**
 * getSigint - To handle the crtl + c call in prompt
 * @sig: The signal handler
 */
void getSigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
