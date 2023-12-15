#include <stdio.h>
#include <stdlib.h>


int main(int ac, char **av)
{
int j;
int sum = 0;

printf("argc or ac = %d\n", ac);
printf("argv content is argv[]\n");

for (j = 0; j < ac; j++)
{
printf("argv[%d] = %s\n", j, av[j]);
sum += atoi(av[j]);
}
printf("sum is %d\n", sum);
return (0);
}
