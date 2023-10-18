#include "code.h"

/**
 * _myhistory - Shows history list, one command per line, preceded by
 * line numbers, starting at 0.
 * @info: Structure containing potential arguments to maintain
 *        a constant function prototype.
 *
 * Return: 0 on success.
 */
int _myhistory(info_t *info)
{
    print_list(info->history);
    return (0);
}

/**
 * unset_alias - Sets an alias to a string.
 * @info: Parameter structure.
 * @str: String alias.
 *
 * Return: 0 on success, 1 on error.
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
 * set_alias - Sets an alias to a string.
 * @info: Parameter structure.
 * @str: String alias.
 *
 * Return: 0 on success, 1 on error.
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
