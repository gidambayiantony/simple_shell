#include "code.h"
/**
 * _strlen - Retrs len of  string
 * @x: string  len check
 *
 * Return: Int strng len
 */
int _strlen(char *x)
{
	int c = 0;

	if (!x)
		return (0);

	while (*x++)
		c++;
	return (c);
}

/**
 * _strcmp - Pfms  compson two strangs
 * @x1: First Strng
 * @x2: Sec Strng
 *
 * Return:  Pstve if x1 > x2, zero if x1 == x2 ,Ngtve if x1 < x2
 */
int _strcmp(char *x1, char *x2)
{
	while (*x1 && *x2)
	{
		if (*x1 != *x2)
			return (*x1 - *x2);
		x1++;
		x2++;
	}
	if (*x1 == *x2)
		return (0);
	else
		return (*x1 < *x2 ? -1 : 1);
}

/**
 * starts_with - Checks needle strts  haystack
 * @haystack: Strng  Search.
 * @needle: Substrng
 *
 * Return: Adds next char  or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Conctnte 2 strngs
 * @dest: Destn buff
 * @src: Source
 *
 * Return: Ptr
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
