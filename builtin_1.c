#include "code.h"
/**
 * _myhistory - Shows hist list, one command by line, preceeds
 *              line numbers, starting 0
 * @info: Structure contains potential arg. To maintain
 *        const function prototype.
 *  Return: 0 in success
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Sets alias to string
 * @info: Param struct
 * @str: str alias
 *
 * Return: 0 in success, 1 in error
 */
int unset_alias(info_t *info, char *str)
{
	char *q, w;
	int vet;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	w = *q;
	*q = 0;
	vet = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*q = w;
	return (vet);
}

/**
 * set_alias - Sets alias to str
 * @info: Param structure
 * @str: Str alias
 *
 * Return: 0 success, else 1
 */
int set_alias(info_t *info, char *str)
{
	char *q;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

