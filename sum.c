#include <stdio.h>
#include <stdlib.h>

/**
 * main - Entry point of the program
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: Always 0 (Success)
 */
int main(int argc, char **argv)
{
int index;
int total = 0;

printf("Argument count (argc): %d\n", argc);
printf("Argument values (argv):\n");

for (index = 0; index < argc; index++)
{
printf("argv[%d] = %s\n", index, argv[index]);

int currentArg = atoi(argv[index]);
if (currentArg != 0 || (currentArg == 0 && argv[index][0] == '0'))
{
total += currentArg;
}
else
{
fprintf(stderr, "Error: Invalid argument '%s'\n", argv[index]);
return (EXIT_FAILURE);
}
}

printf("Sum of integers is %d\n", total);
return (EXIT_SUCCESS);
}
