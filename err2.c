#include "code.h"

/**
 * _erratoi - string to int
 * @s: str .
 * Return: no num return 0 , converted no otherwise
 *       return -1 on error
 */
int _erratoi(char *s)
{
	int h = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (h = 0;  s[h] != '\0'; h++)
	{
		if (s[h] >= '0' && s[h] <= '9')
		{
			result *= 10;
			result += (s[h] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error -output error messages
 * @info: parameter & return info struct
 * @estr: string having specified type of errors
 * Return: no no 0, converted number otherwise
 *        return -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - fuctn print decimals (integer) num (base 10)
 * @input: input
 * @fd: filedescriptor  write on
 *
 * Return: number of char printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int h, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (h = 1000000000; h > 1; h /= 10)
	{
		if (_abs_ / h)
		{
			__putchar('0' + current / h);
			count++;
		}
		current %= h;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - function, clone of itoa
 * @num: no
 * @base: base
 * @flags: arg flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - functn replace first instance of '#' with '\0'
 * @buf: str address modify
 *
 * Return:  0 Success;
 */
void remove_comments(char *buf)
{
	int x;

	for (x = 0; buf[x] != '\0'; x++)
		if (buf[x] == '#' && (!x || buf[x - 1] == ' '))
		{
			buf[x] = '\0';
			break;
		}
}
