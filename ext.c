#include "code.h"

/**
 * _strncpy - Copy 'n' characters from 'src' to 'dest'.
 * @dest: Destination string to copy to.
 * @src: Source string.
 * @n: Number of characters to copy.
 *
 * Return: Pointer to the concatenated string.
 */
char *_strncpy(char *dest, char *src, int n)
{
    int h, v;
    char *s = dest;

    h = 0;
    while (src[h] != '\0' && h < n - 1)
    {
        dest[h] = src[h];
        h++;
    }
    if (h < n)
    {
        v = h;
        while (v < n)
        {
            dest[v] = '\0';
            v++;
        }
    }
    return (s);
}

/**
 * _strncat - Concatenate 'n' characters from 'src' to 'dest'.
 * @dest: First string.
 * @src: Second string.
 * @n: Number of bytes to maximally use.
 *
 * Return: Pointer to the concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
    int z, v;
    char *s = dest;

    z = 0;
    v = 0;
    while (dest[z] != '\0')
        z++;
    while (src[v] != '\0' && v < n)
    {
        dest[z] = src[v];
        z++;
        v++;
    }
    if (v < n)
        dest[z] = '\0';
    return (s);
}

/**
 * _strchr - Locate a character 'c' in the string 's'.
 * @s: String to be parsed.
 * @c: Character to find.
 *
 * Return: Pointer to the memory location or NULL if not found.
 */
char *_strchr(char *s, char c)
{
    do
    {
        if (*s == c)
            return (s);
    } while (*s++ != '\0');

    return (NULL);
}
