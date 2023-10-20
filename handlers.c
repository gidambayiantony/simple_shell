#include "code.h"
/**
 * **strtow - Splits and duplicates string into words
 * @str: String
 * @d: String Del
 * Return: Ptr   array of strings, else NULL on failure
 */

char **strtow(char *str, char *d)
{
	int y, x, u, n, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (y = 0; str[y] != '\0'; y++)
		if (!is_delim(str[y], d) && (is_delim(str[y + 1], d) || !str[y + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (y = 0, x = 0; x < numwords; x++)
	{
		while (is_delim(str[y], d))
			y++;
		u = 0;
		while (!is_delim(str[y + u], d) && str[y + u])
			u++;
		s[x] = malloc((u + 1) * sizeof(char));
		if (!s[x])
		{
			for (u = 0; u < x; u++)
				free(s[u]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < u; n++)
			s[x][n] = str[y++];
		s[x][n] = 0;
	}
	s[x] = NULL;
	return (s);
}

/**
 * **strtow2 - Split or duplicates string into words
 * @str: Str Input
 * @d: Delim
 * Return: Ptr to  array of strings, else NULL on failure
 */
char **strtow2(char *str, char d)
{
	int h, j, u, n, numwords = 0;
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
	for (h = 0, j = 0; j < numwords; j++)
	{
		while (str[h] == d && str[h] != d)
			h++;
		u = 0;
		while (str[h + u] != d && str[h + u] && str[h + u] != d)
			u++;
		s[j] = malloc((u + 1) * sizeof(char));
		if (!s[j])
		{
			for (u = 0; u < j; u++)
				free(s[u]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < u; n++)
			s[j][n] = str[h++];
		s[j][n] = 0;
	}
	s[j] = NULL;
	return (s);
}

