#include "code.h"
/**
 * _strlen - Returns   a string
 * @s: string  to check
 *
 * Return: Intr string lenght
 */
int _strlen(char *s)
{
	int y = 0;

	if (!s)
		return (0);

	while (*s++)
		y++;
	return (y);
}

/**
 * _strcmp -   comparison of two strangs
 * @s1: First Strinng
 * @s2: Second Strng
 *
 * Return:  Positive if s1 > s2, zero if s1 == s2 ,Negative if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with -test if needle starts with haystack
 * @haystack: Str  Search
 * @needle: Substring
 *
 * Return: Address of  char  or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Concat 2 strings
 * @dest: Destn buff
 * @src: Bufr Source
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
