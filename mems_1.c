#include "code.h"
/**
 * bfree -it rees pointer and NULLs the address
 * @ptr: Address of  pointer to be freed
 *
 * Return: on Success 1, else 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
