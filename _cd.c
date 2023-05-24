#include "main.h"

/**
 * main - main function
 *
 * Return: always 0
 */
int main(void)
{
char *command, *home_dir = getenv("HOME"); /* home env */
while (1)
{
printf("$ ");
command = malloc(1024 * sizeof(char));
fgets(command, 1024, stdin);
command[strcspn(command, "\n")] = '\0';
if (strcmp(command, "cd") == 0)
{
chdir(home_dir);
}
else if (strncmp(command, "cd ", 3) == 0)
{
char *arg = command + 3;
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
