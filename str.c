#include "code.h"
/**
 * _strcpy - it Copy String
 * @dest: De
 * @src: Source
 *
 * Return: Des Ptr
 */
char *_strcpy(char *dest, char *src)
{
	int y = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[y])
	{
		dest[y] = src[y];
		y++;
	}
	dest[y] = 0;
	return (dest);
}

/**
 * _strdup - it transforms and deplicates the String
 * @str: String Duplicate transform
 *
 * Return: Duplicated string pointer
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - Print input str
 * @str: Printed string
 *
 * Return: Null
 */
void _puts(char *str)
{
	int y = 0;

	if (!str)
		return;
	while (str[y] != '\0')
	{
		_putchar(str[y]);
		y++;
	}
}

/**
 * _putchar - outputss  char c to stdout
 * @c:  char to be  printed
 *
 * Return: 1 0n success
 * -1 on error is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int y;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || y >= WRITE_BUF_SIZE)
	{
		write(1, buf, y);
		y = 0;
	}
	if (c != BUF_FLUSH)
		buf[y++] = c;
	return (1);
}
