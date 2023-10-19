#include "code.h"
/**
 * _strcpy - Cpy Strng
 * @dest: Destn
 * @src: Source
 *
 * Return: Desn Ptr
 */
char *_strcpy(char *dest, char *src)
{
	int c = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[c])
	{
		dest[c] = src[c];
		c++;
	}
	dest[c] = 0;
	return (dest);
}

/**
 * _strdup - Duplct  Stn
 * @str: Stn  Dup
 *
 * Return: Dup stn ptr
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
 * _puts - Prnt inp stn
 * @str: Prin strn
 *
 * Return: Null
 */
void _puts(char *str)
{
	int c = 0;

	if (!str)
		return;
	while (str[c] != '\0')
	{
		_putchar(str[c]);
		c++;
	}
}

/**
 * _putchar - Wrt  char u stdout
 * @l:  char prn
 *
 * Return: 1 in success
 * -1 on error is retn, and errno set apprpt
 */
int _putchar(char l)
{
	static int c;
	static char buf[WRITE_BUF_SIZE];

	if (l == BUF_FLUSH || c >= WRITE_BUF_SIZE)
	{
		write(1, buf, c);
		c = 0;
	}
	if (l != BUF_FLUSH)
		buf[c++] = l;
	return (1);
}
