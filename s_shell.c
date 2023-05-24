#include "main.h"
/**
 * main - main function
 * Return: always 0
 */
int main(void)
{
char *args[MAX_ARGS], cmd[MAX_INPUT], *tkn;
int loop = 1, i = 0;
pid_t pid;
while (loop)
{
printf("($) ");
fflush(stdout);
fgets(cmd, MAX_INPUT, stdin);
if (cmd[strlen(cmd) - 1] == '\n')
{
cmd[strlen(cmd) - 1] = '\0';
}
tkn = strtok(cmd, " ");
for (i = 0; tkn != NULL; i++)
{
args[i] = tkn;
tkn = strtok(NULL, " ");
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
perror("./shell: No such file or directory");
exit(EXIT_FAILURE);
}
else if (pid < 0)
{
perror("fork");
exit(EXIT_FAILURE);
}
else
{
wait(NULL);
}
}
return (0);
}
