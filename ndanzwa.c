#include "main.h"

/**
 * usandisaize - gets
 * @info: parameter
 *
 * Return: allocated
 */

char *usandisaize(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * huyatidyezve - creates
 * @info: the parameter
 *
 * Return: 1 on success
 */
int huyatidyezve(info_t *info)
{
	ssize_t fd;
	char *filename = usandisaize(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		maihwi(node->str, fd);
		rufaro('\n', fd);
	}
	rufaro(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * goramakora - reads
 * @info: the parameter
 *
 * Return: value
 */
int goramakora(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = usandisaize(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			makoraa(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		makoraa(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		mabiribobi(&(info->history), 0);
	makora(info);
	return (info->histcount);
}

/**
 * makoraa - add
 * @info: info
 * @buf: buffer
 * @linecount: count
 *
 * Return: Always 0
 */
int makoraa(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * makora - renumbers
 * @info: info
 *
 * Return: the new histcount
 */
int makora(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
