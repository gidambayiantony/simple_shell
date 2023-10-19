#include "code.h"

/**
 * get_history_file - Fetch the history file
 * @info: Parameter structure
 *
 * Return: Dynamically allocated string
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - Appends data to an existing file
 * @info: Parameter structure
 *
 * Return: 1 on success, -1 on failure
 */
int write_history(info_t *info)
{
	ssize_t uv;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	uv = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (uv == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, uv);
		_putfd('\n', uv);
	}
	_putfd(BUF_FLUSH, uv);
	close(uv);
	return (1);
}

/**
 * read_history - Read the history file
 * @info: Parameter structure
 *
 * Return: The number of history entries loaded on success, 0 on failure
 */
int read_history(info_t *info)
{
	int z, last = 0, linecount = 0;
	ssize_t uv, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	uv = open(filename, O_RDONLY);
	free(filename);
	if (uv == -1)
		return (0);
	if (!fstat(uv, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(uv, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(uv);
	for (z = 0; z < fsize; z++)
		if (buf[z] == '\n')
		{
			buf[z] = 0;
			build_history_list(info, buf + last, linecount++);
			last = z + 1;
		}
	if (last != z)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * append_to_history - Add a new entry to the history linked list
 * @info: Parameter structure containing potential arguments. Used to maintain
 * @buf: The buffer containing the history entry
 * @linecount: The line count for the history entry
 *
 * Return: Always returns 0, indicating success
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * update_history_numbers - Update the numbering in the history linked list
 * @info: Parameter structure containing arguments
 *
 * Return: The new value of histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int z = 0;

	while (node)
	{
		node->num = z++;
		node = node->next;
	}
	return (info->histcount = z);
}
