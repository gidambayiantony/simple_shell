#include "code.h"

/**
 * _strncpy - Copy string.
 * @dest: Destination string to copy to.
 * @src: String source.
 * @n: Amount of characters to copy.
 * Return: Concatenated string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int h, k;
	char *s = dest;

	h = 0;
	while (src[h] != '\0' && h < n - 1)
	{
		dest[h] = src[h];
		h++;
	}
	if (h < n)
	{
		k = h;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (s);
}

/**
 * _strncat - Concatenates two strings.
 * @dest: First string.
 * @src: Second string.
 * @n: Amount of bytes to maximally use.
 * Return: Concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int x, k;
	char *s = dest;

	x = 0;
	k = 0;
	while (dest[x] != '\0')
		x++;
	while (src[k] != '\0' && k < n)
	{
		dest[x] = src[k];
		x++;
		k++;
	}
	if (k < n)
		dest[x] = '\0';
	return (s);
}

/**
 * _strchr - Locate a character in the string.
 * @s: String to be parsed.
 * @c: Character to look for.
 * Return: (s) a pointer to the memory area s.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
