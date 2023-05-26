#include "main.h"

/**
 *nyambuya - function
 * @str: str
 *
 * Return: Nothing
 */
void nyambuya(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		dhidhaguru(str[i]);
		i++;
	}
}

/**
 * dhidhaguru - function
 * @c: c
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int dhidhaguru(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * rufaro - function
 * @c: c
 * @fd: fd
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int rufaro(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *maihwi - prints
 * @str: str
 * @fd: fd
 *
 * Return: the number
 */
int maihwi(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += rufaro(*str++, fd);
	}
	return (i);
}
