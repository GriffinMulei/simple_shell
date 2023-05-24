#include "shell.h"
/**
 * exit_shell - Exit the shell
 *
 * Return: void
 */

void exit_shell(void)
{
	{
		exit(child_exit_status);
	}
	exit(EXIT_SUCCESS);
}
