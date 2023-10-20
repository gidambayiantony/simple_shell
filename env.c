#include "code.h"

/**
 * _myenv - Print current environment.
 * @info: Structure containing potential arguments. Used for maintaining
 *          constant function prototype.
 * Return: Always 0 Success.
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Get the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Environment variable name.
 *
 * Return: The value of the environment variable.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 *  Return: Always 0 Success.
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments.\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments. Used for maintaining
 *        a constant function prototype.
 * Return: Always 0 Success.
 */
int _myunsetenv(info_t *info)
{
	int h;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (h = 1; h <= info->argc; h++)
		_unsetenv(info, info->argv[h]);

	return (0);
}

/**
 * populate_env_list - Populate the environment linked list.
 * @info: Structure containing potential arguments. Used for maintaining
 *          a constant function prototype.
 * Return: Always 0 Success.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t h;

	for (h = 0; environ[h]; h++)
		add_node_end(&node, environ[h], 0);
	info->env = node;
	return (0);
}
