#include "code.h"

/**
 * _myenv - output current env
 * @info: Struct having potential args.  for maintaining
 *          constant function prototype.
 * Return: 0 Success
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - obtain value of  env var
 * @info: Struct having potential arguments.
 * @name: env variable name
 *
 * Return: a value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - set new environ var,
 *             and modify the existing
 * @info: Struc having potential arguments. Used for maintain
 *        constant function prototype.
 *  Return: Always 0 Success
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - rem an env var
 * @info: Structure having potential arg. Used for maintaining
 *        constant function prototype.
 * Return:  0 Success
 */
int _myunsetenv(info_t *info)
{
	int h;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (h = 1; h <= info->argc; h++)
		_unsetenv(info, info->argv[h]);

	return (0);
}

/**
 * populate_env_list -  Populate env linked list
 * @info: Structure having potential arg. for maintaining
 *          constant function prototype.
 * Return: 0 Success
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


