#include "main.h"

/**
 * print_env - prints environment varriables
 * @info: Structure cintaining arguments to mantain constant function prototype
 * Return: always 0
 */

int print_env(const char *keep_var)
{
	char **env;
	size_t keep_var_length = strlen(keep_var);

	for (env = environ; *env != NULL; ++env)
	{
		if (strncmp(*env, keep_var, keep_var_length) != 0 ||
				(*env)[keep_var_length] != '=')
		{
			if (unsetenv(*env) == -1)
			{
				perror("unsetnv");
				return (-1);
			}
		}
	}
	if (execlp("env", "env", (char *)NULL) == -1)
	{
		fprintf(stderr, "execlp failed: %s\n", strerror(errno));
		return (-1);
	}
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing arguments to mantiain constant prototype.
 * Return: always 0 
 */

int _myenv(info_t *info)

{
	print_list_str(info->env);

	return (0);
}

/**
 * _myunsetenv - Remove an environmnt variable
 *@info: structure containing arguments to mentain constant function prototype 
 * Return: Always 0
 */

int _myunsetenv(info_t *info)
{
	int i;
	if (info->argc == 1)
	{
		_put("too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)

	return (0);
}
