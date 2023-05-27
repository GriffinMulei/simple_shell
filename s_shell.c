#include "main.h"

/**
 * main - main function
 * Return: always success(0)
 */
int main(void)
{
char *args[MAX_ARGS], cmd[MAX_INP], *token;
int loop = 1, i = 0;
pid_t pid;
while (loop)
{
printf("$ ");
fflush(stdout);
fgets(cmd, MAX_INP, stdin);
if (cmd[strlen(cmd) - 1] == '\n')
{
cmd[strlen(cmd) - 1] = '\0';
}
token = strtok(cmd, " ");
for (i = 0; token != NULL; i++)
{
args[i] = token;
token = strtok(NULL, " ");
}
args[i] = NULL;
if (strcmp(args[0], "exit") == 0)
{
loop = 0;
break;
}
pid = fork();
if (pid == 0)
{
execvp(args[0], args);
perror("execvp"); // Print an error message if execvp fails
exit(EXIT_FAILURE);
}
else if (pid < 0)
{
perror("fork");
exit(EXIT_FAILURE);
}
else
{
wait(NULL); // Wait for the child process to finish
}
}
return (0);
}
