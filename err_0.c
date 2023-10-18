#include "code.h"

/**
 * _eputs - Print input string to stderr.
 * @str: The str to print.
 *
 * Return: Nill
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
 * _eputchar - Write character 'c' to stderr.
 * @c: Character to print.
 *
 * Return: Success on 1.
 *         -1 on error.
 */
int _eputchar(char c)
{
    static int z;
    static char buf[WRITE_BUF_SIZE];

    if (z == BUF_FLUSH || z >= WRITE_BUF_SIZE)
    {
        write(2, buf, z);
        z = 0;
    }
    if (z != BUF_FLUSH)
        buf[z++] = c;
    return (1);
}

/**
 * _putfd - Write character 'c' to the given file descriptor 'fd'.
 * @c: Character to print.
 * @fd: File descriptor to write on.
 *
 * Return: 1 on success.
 *         -1 on error.
 */
int _putfd(char c, int fd)
{
    static int h;
    static char buf[WRITE_BUF_SIZE];

    if (h == BUF_FLUSH || h >= WRITE_BUF_SIZE)
    {
        write(fd, buf, h);
        h = 0;
    }
    if (h != BUF_FLUSH)
        buf[h++] = c;
    return (1);
}

/**
 * _putsfd - Write input string to the given file descriptor 'fd'.
 * @str: String to be printed.
 * @fd: File descriptor.
 *
 * Return: Number of characters written.
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
    return h;
}
