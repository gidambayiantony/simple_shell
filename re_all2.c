#include "code.h"
/**
 * _memset - gets memory with  constant byte
 * @s: Ptr 
 * @b: byte to be  filedl *s with
 * @n: Amount of bytes
 * Return: Ptr memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int y;

	for (y = 0; y < n; y++)
		s[y] = b;
	return (s);
}

/**
 * ffree - Frees  str of str
 * @pp: Str of Str
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - Reallocates   memory
 * @ptr: ptr block
 * @old_size: Byte size
 * @new_size: Byte  new block
 *
 * Return: ptr to block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}


