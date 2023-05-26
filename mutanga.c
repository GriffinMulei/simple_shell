#include "main.h"

/**
 * mupfanha - frees
 * @ptr: addres
 *
 * Return: 1 if freed
 */
int mupfanha(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
