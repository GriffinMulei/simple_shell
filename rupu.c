#include "main.h"

/**
 * hsh - main
 * @info: the paramete
 * @av: the argument
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (shombeka(info))
			_puts("$ ");
		dhidhaguru(BUF_FLUSH);
		r = tipeiwo(info);
		if (r != -1)
		{
			pakatishatei(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				ruvarangu(info);
		}
		else if (shombeka(info))
			_putchar('\n');
		zvekutodaro(info, 0);
	}
	huyatidyezve(info);
	zvekutodaro(info, 1);
	if (!shombeka(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds
 * @info: the parameter
 *
 * Return: -1 if builtin not found
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", rubatsiro},
		{"history", pakufambayzia},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * ruvarangu - find
 * @info: the paramet
 *
 * Return: void
 */
void ruvarangu(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = tipeinzira(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		ruvarashe(info);
	}
	else
	{
		if ((shombeka(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			ruvarashe(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * ruvarashe - forks
 * @info: the parameter
 *
 * Return: void
 */
void ruvarashe(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			zvekutodaro(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
