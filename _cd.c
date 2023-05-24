#include "main.h"

/**
 * main - main function
 *
 * Return: always 0
 */
int main(void)
{
char *command, *home_dir = getenv("HOME"); /* home env */
int n = 3;
while (1)
{
printf("$ ");
command = malloc(buf_size * sizeof(char));
fgets(command, buf_size, stdin);
command[strcspn(command, "\n")] = '\0';
if (strcmp(command, "cd") == 0)
{
chdir(home_dir);
}
else if (strncmp(command, "cd ", n) == 0)
{
char *arg = n + command;
chdir(arg);
}
else
{
system(command); /* execute cmd */
}
free(command);
}
return (0);
}
