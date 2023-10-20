#include "code.h"

/**
 * list_len - identifies length of linked list
 * @h: Ptr to  node
 *
 * Return:  size
 */
size_t list_len(const list_t *h)
{
	size_t y = 0;

	while (h)
	{
		h = h->next;
		y++;
	}
	return (y);
}

/**
 * list_to_strings - array of str of the list->str
 * @head: ptr to node
 *
 * Return: str Arrays
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t y = list_len(head), x;
	char **strs;
	char *str;

	if (!head || !y)
		return (NULL);
	strs = malloc(sizeof(char *) * (y + 1));
	if (!strs)
		return (NULL);
	for (y = 0; node; node = node->next, y++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (x = 0; x < y; x++)
				free(strs[x]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[y] = str;
	}
	strs[y] = NULL;
	return (strs);
}


/**
 * print_list -writes  elements of a list_t linked list
 * @h: ptr to node
 *
 * Return:list size
 */
size_t print_list(const list_t *h)
{
	size_t y = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		y++;
	}
	return (y);
}

/**
 * node_starts_with -  node  with prefix
 * @node: P to list head
 * @prefix: Str  match
 * @c: next char after prefix to match
 *
 * Return: Null or match node
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - obtain index of a node
 * @head: Pointing list head
 * @node: Pointing node
 *
 * Return: -1 or Index node
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t y = 0;

	while (head)
	{
		if (head == node)
			return (y);
		head = head->next;
		y++;
	}
	return (-1);
}
