#include "code.h"
/**
 * _memset - Fills memory const byte
 * @k: Ptr to  mem area
 * @y: byte to fill *k with
 * @v: Amnt of bytes
 * Return: Ptr the mem area k
 */
char *_memset(char *k, char y, unsigned int v)
{
	unsigned int c;

	for (c = 0; c < v; c++)
		k[c] = y;
	return (k);
}

/**
 * ffree - Frees  strn of strn
 * @tt: Strg  Strng
 */
void ffree(char **tt)
{
	char **x = tt;

	if (!tt)
		return;
	while (*tt)
		free(*tt++);
	free(x);
}

/**
 * _realloc - Reallocates  blck mem
 * @ptr: ptr prev blck
 * @old_size: size
 * @new_size: Byte new block
 *
 * Return: ptr to blck
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *t;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	t = malloc(new_size);
	if (!t)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		t[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (t);
}
