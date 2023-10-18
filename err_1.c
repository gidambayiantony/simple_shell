#include "code.h"

/**
 * _erratoi - convert str to interger
 * @s: The input string for conversion.
 * Return: It returns 0 when no numbers are present; 
 *       In case of an error, it returns -1
 */
int _erratoi(char *s)
{
	int h = 0;
	unsigned long int result = 0;

	if (*m == '+')
		m++;  
	for (h = 0;  m[h] != '\0'; h++)
	{
		if (m[h] >= '0' && m[h] <= '9')
		{
			result *= 10;
			result += (m[h] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - display error msg
 * @info: Param & return infomation struct
 * @estr: str holds certain type of errors
 * Return: Return 0 if there are no numbers, otherwise
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
 * print_d - Print decimals and numbers
 * @input: The input
 * @fd:  the file descriptor to write on
 *
 * Return: the number of characters printed
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
		if (_abs_ / i)
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
 * convert_number - Clone of itoa
 * @num: the num
 * @base: the base
 * @flags: the arg flags
 *
 * Return: str
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
 * remove_comments - Function that  replaces the first instance of '#' with '\0'
 * @buf: the str address to change
 *
 * Return: 0 on Success;
 */
void remove_comments(char *buf)
{
	int z;

	for (z = 0; buf[z] != '\0'; z++)
		if (buf[z] == '#' && (!z || buf[z - 1] == ' '))
		{
			buf[z] = '\0';
			break;
		}
}
