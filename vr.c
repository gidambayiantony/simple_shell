#include "code.h"
/**
 * is_chain - Test current char buff is chain delim
 * @info:  Par Strct
 * @buf: Char Buff
 * @v: Adds of buf
 *
 * Return: in Success 1, in 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *v)
{
	size_t x = *v;

	if (buf[x] == '|' && buf[x + 1] == '|')
	{
		buf[x] = 0;
		x++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[x] == '&' && buf[x + 1] == '&')
	{
		buf[x] = 0;
		x++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[x] == ';') /* found end  command */
	{
		buf[x] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*v = x;
	return (1);
}

/**
 * check_chain -  entr pnt
 * @info: Param Strct
 * @buf: Buff Char
 * @p: Adres currnt pos
 * @i: Start pos in buf
 * @len: Buf len
 * Return: void
 */
void check_chain(info_t *info, char *buf, size_t *v, size_t i, size_t len)
{
	size_t w = *v;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			w = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			w = len;
		}
	}

	*v = w;
}

/**
 * replace_alias - Replcs an alise
 * @info:  Param Strct
 *
 * Return: replaced return 1, else 0
 */
int replace_alias(info_t *info)
{
	int x;
	list_t *node;
	char *u;

	for (x = 0; x < 10; x++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		u = _strchr(node->str, '=');
		if (!u)
			return (0);
		u = _strdup(u + 1);
		if (!u)
			return (0);
		info->argv[0] = u;
	}
	return (1);
}

/**
 * replace_vars - Rplcs var
 * @info: Param Strct
 *
 * Return: once repl in 1, else in 0
 */
int replace_vars(info_t *info)
{
	int x = 0;
	list_t *node;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

		if (!_strcmp(info->argv[x], "$?"))
		{
			replace_string(&(info->argv[x]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			replace_string(&(info->argv[x]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[x][1], '=');
		if (node)
		{
			replace_string(&(info->argv[x]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[x], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Rep Stng
 * @old: Adres old strng
 * @new: Next Strng
 *
 * Return:once replaced in 1, in else 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
