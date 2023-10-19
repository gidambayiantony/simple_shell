#include "code.h"

/**
 * clear_info - Clears info_t struct.
 * @info: Pointer to the structure to clear.
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Initializes info_t struct.
 * @info: Pointer to the structure to initialize.
 * @av: Argument vector.
 */
void set_info(info_t *info, char **av)
{
	int h = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (h = 0; info->argv && info->argv[h]; h++)
			;
		info->argc = h;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Clears info_t struct fields.
 * @info: Ptr  the structure to free.
 * @all: Freeing all fields if set to 1.
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readuv > 2)
			close(info->readuv);
		_putchar(BUF_FLUSH);
	}
}
