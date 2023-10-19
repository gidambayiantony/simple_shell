#include "code.h"
/**
 * **strtow - duplicates string into words
 * @str: str input
 * @d: Str Del
 * Return: Ptr to  array of strings, else NULL on failure
 */

char **strtow(char *str, char *d)
{
	int x, y, q, o, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!is_delim(str[x], d) && (is_delim(str[x + 1], d) || !str[x + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (y = 0, y = 0; y < numwords; y++)
	{
		while (is_delim(str[x], d))
			x++;
		q = 0;
		while (!is_delim(str[x + q], d) && str[x + q])
		q++;
		s[y] = malloc((q + 1) * sizeof(char));
		if (!s[y])
		{
			for (q = 0; q < x; q++)
				free(s[q]);
			free(s);
			return (NULL);
		}
		for (o = 0; o < q; o++)
			s[x][o] = str[y++];
		s[y][o] = 0;
	}
	s[y] = NULL;
	return (s);
}

/**
 * **strtow2 - deplicates string into words
 * @str: Str Input
 * @d: Delim
 * Return: P to  array of str, else NULL on failure
 */
char **strtow2(char *str, char d)
{
	int h, l, q, o, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (h = 0; str[h] != '\0'; h++)
		if ((str[h] != d && str[h + 1] == d) ||
				    (str[h] != d && !str[h + 1]) || str[h + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (h = 0, l = 0; l < numwords; l++)
	{
		while (str[h] == d && str[h] != d)
			h++;
		q = 0;
		while (str[h + q] != d && str[h + q] && str[h + q] != d)
			q++;
		s[l] = malloc((q + 1) * sizeof(char));
		if (!s[l])
		{
			for (q = 0; q < l; q++)
				free(s[q]);
			free(s);
			return (NULL);
		}
		for (o = 0; o < q; o++)
			s[l][o] = str[h++];
		s[l][o] = 0;
	}
	s[l] = NULL;
	return (s);
}

