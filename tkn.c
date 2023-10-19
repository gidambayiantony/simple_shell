#include "code.h"
/**
 * **strtow - Splts strng into wrds
 * @str: Strn inp
 * @q: String Deli
 * Return: Ptr to  array of strngs, else NULL in fail
 */

char **strtow(char *str, char *q)
{
	int x, y, w, r, numwords = 0;
	char **t;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!q)
		q = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!is_delim(str[x], q) && (is_delim(str[x + 1], q) || !str[x + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	t = malloc((1 + numwords) * sizeof(char *));
	if (!t)
		return (NULL);
	for (x = 0, y = 0; y < numwords; y++)
	{
		while (is_delim(str[y], q))
			x++;
		w = 0;
		while (!is_delim(str[y + x], q) && str[y + w])
			w++;
		t[y] = malloc((w + 1) * sizeof(char));
		if (!t[x])
		{
			for (w = 0; w < x; w++)
				free(t[w]);
			free(t);
			return (NULL);
		}
		for (r = 0; r < w; r++)
			t[x][r] = str[x++];
		t[x][r] = 0;
	}
	t[x] = NULL;
	return (t);
}

/**
 * **strtow2 - Splt stn int word
 * @str: String Input
 * @v: Delim
 * Return: Ptr array strings, else NULL in fail
 */
char **strtow2(char *str, char v)
{
	int q, w, e, r, numwords = 0;
	char **p;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (q = 0; str[q] != '\0'; q++)
		if ((str[q] != v && str[q + 1] == v) ||
				    (str[q] != v && !str[q + 1]) || str[q + 1] == v)
			numwords++;
	if (numwords == 0)
		return (NULL);
	p = malloc((1 + numwords) * sizeof(char *));
	if (!p)
		return (NULL);
	for (q = 0, w = 0; w < numwords; w++)
	{
		while (str[q] == v && str[q] != v)
			q++;
		e = 0;
		while (str[q + e] != v && str[q + e] && str[q + e] != v)
			e++;
		p[w] = malloc((e + 1) * sizeof(char));
		if (!p[w])
		{
			for (e = 0; e < w; e++)
				free(p[e]);
			free(p);
			return (NULL);
		}
		for (r = 0; r < e; r++)
			p[w][r] = str[q++];
		p[w][r] = 0;
	}	
	p[w] = NULL;
	return (p);
}
