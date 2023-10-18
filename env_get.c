#include "code.h"

/**
 * get_environ - Copy environment variables into an array of strings.
 * @info: Structure holding arguments.
 *
 * Return: Pointer to an array of strings.
 */
char **get_environ(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable.
 * @info: Structure holding arguments.
 * @var: String environment variable property.
 *
 * Return: 1 on successful delete, else 0.
 */
int _unsetenv(info_t *info, char *var)
{
    list_t *node = info->env;
    size_t h = 0;
    char *q;

    if (!node || !var)
        return (0);

    while (node)
    {
        q = starts_with(node->str, var);
        if (q && *q == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), h);
            h = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        h++;
    }
    return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable.
 * @info: Structure holding arguments.
 * @var: String environment variable property.
 * @value: String environment variable value.
 *
 * Return: 0 on success, else 1.
 */
int _setenv(info_t *info, char *var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *q;

    if (!var || !value)
        return (0);

    buf = malloc(_strlen(var) + _strlen(value) + 2);
    if (!buf)
        return (1);
    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);
    node = info->env;
    while (node)
    {
        q = starts_with(node->str, var);
        if (q && *q == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return (0);
        }
        node = node->next;
    }
    add_node_end(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;
    return (0);
}
