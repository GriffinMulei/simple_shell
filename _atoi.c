#include "shell.h"

/**
 * interactive - interactive mode(returns true if shell is interactive mode)
 * @info: sruct address
 *
 * return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * _atoi - convert string to interger
 * @s: the string to be converted
 * Return an integer
 */

int _atoi(char *s)
{
	int i, sign = 1;
	unsigned int results = 0;
	int flag = 0, output;
	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		while (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			results *= 10;
			results += (s[i] - '0');
		}
		if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -results;
	else
		output = results;
	return (output);
}

/*
 * _isalpha - checks if a character is alphebetic
 * @c: The character ti input
 * Return: 1 if c is alphabetic, 0 if otherwise
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
	{
		return (0);
	}
}

/** 
*is_delim - checks if delimeter is a character
*@delim: the delimeter sting
*@c: the character to check
*Return: 1 if true, 0 if otherwise
*/
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
