#include <stdio.h>

/**
 * main - entry point function
 *
 * Return: always 0
 */
int main(void)
{
char command[256];
int loop = 1;
while (loop) /* start of infinite loop */
{
printf("$ ");   /* prompt to user */
fgets(command, 256, stdin); /* collect input command */
system(command); /* run entered command */
}
return (0);
}
