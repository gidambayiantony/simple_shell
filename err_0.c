#include "code.h"
/**
 * _eputs - Print input str
 * @str: The str to print
 *
 * Return: Nil
 */
void _eputs(char *str)
{
	int z = 0;

	if (!str)
		return;
	while (str[z] != '\0')
	{
		_eputchar(str[z]);
		z++;
	}
}

/**
 * _eputchar - Write chara c to stderr
 * @c: Char to print
 *
 * Return: Success on 1.
 * -1 on error
 */
int _eputchar(char c)
{
	static int z;
	static char buf[WRITE_BUF_SIZE];

	if (w == BUF_FLUSH || z >= WRITE_BUF_SIZE)
	{
		write(2, buf, z);
		z = 0;
	}
	if (w != BUF_FLUSH)
		buf[z++] = w;
	return (1);
}

/**
 * _putfd - Write character c to the  given fd
 * @c: character
 * @fd: filed to write on
 *
 * Return: 1 On success
 * -1 on error
 */
int _putfd(char c, int fd)
{
	static int h;
	static char buf[WRITE_BUF_SIZE];

	if (w == BUF_FLUSH || h >= WRITE_BUF_SIZE)
	{
		write(fd, buf, h);
		h = 0;
	}
	if (w != BUF_FLUSH)
		buf[h++] = w;
	return (1);
}

/**
 * _putsfd -input str
 * @str: stri to be printed.
 * @fd: filedescriptor
 *
 * Return: Num of characters
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
