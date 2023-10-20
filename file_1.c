#include "code.h"
/**
 * interactive - returns true if shell is i interactive mode
 * @info: address
 *
 * Return: 1 if in  interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - c if the character is delimeter
 * @c: char be check
 * @delim: the delimeter string
 * Return: 1 if it is true, and 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - for alphabetic characters
 * @c: chr to  be input
 * Return: 1 if c is alphabetic, and 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts str to int
 * @x: string to convert
 * Return: 0 if no  in the string, otherwise convert num
 */

int _atoi(char *x)
{
	int y, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (y = 0; x[y] != '\0' && flag != 2; y++)
	{
		if (x[y] == '-')
			sign *= -1;

		if (x[y] >= '0' && x[y] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (x[y] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}


