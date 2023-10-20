#include "code.h"

/**
 * _eputs - Print the input string.
 * @str: String to print.
 *
 * Return: Nothing.
 */
void _eputs(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_eputchar(str[x]);
		x++;
	}
}

/**
 * _eputchar - Write the character c to stderr.
 * @c: The character to print.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}

/**
 * _putfd - Write character c to the given file descriptor.
 * @c: Character to be printed.
 * @fd: The file descriptor to write on.
 *
 * Return: Return 1 on success.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int h;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || h >= WRITE_BUF_SIZE)
	{
		write(fd, buf, h);
		h = 0;
	}
	if (c != BUF_FLUSH)
		buf[h++] = c;
	return (1);
}

/**
 * _putsfd - Print the input string.
 * @str: String to print.
 * @fd: File descriptor to write.
 *
 * Return: Number of characters put.
 */
int _putsfd(char *str, int fd)
{
	int h = 0;

	if (!str)
		return (0);
	while (*str)
	{
		h += _putfd(*str++, fd);
	}
	return (h);
}
