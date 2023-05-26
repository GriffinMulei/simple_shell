#include "main.h"

/**
 * zvapera - test
 * @info: inf
 * @buf: buf
 * @p: p
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int zvapera(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * tapera - checks
 * @info: the parameter struct
 * @buf: param
 * @p: param
 * @i: param
 * @len: len
 *
 * Return: Void
 */
void tapera(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * marooro - replaces
 * @info: the parameter
 *
 * Return: 1 if replaced, 0 otherwise
 */
int marooro(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * masowe - replaces
 * @info: the parameter
 *
 * Return: 1 if replaced, 0 otherwise
 */
int masowe(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			shombe(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			shombe(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			shombe(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		shombe(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * shombe - replaces
 * @old: old
 * @new: new
 *
 * Return: 1 if replaced, 0 otherwise
 */
int shombe(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
