#include "code.h"
/**
 * is_cmd - file is  executable command
 * @info: Inf Strct
 * @path: File
 *
 * Return: in success 1, in else 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Dup Char
 * @pathstr: Strng path
 * @start:  Index
 * @stop: Index
 *
 * Return: Buffer next ptr
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int c = 0, o = 0;

	for (o = 0, c = start; c < stop; c++)
		if (pathstr[c] != ':')
			buf[o++] = pathstr[c];
	buf[o] = 0;
	return (buf);
}

/**
 * find_path - cmd the string path
 * @info: Inf Strct
 * @pathstr: Strin Path
 * @cmd: to find
 *
 * Return: if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int c = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[c] || pathstr[c] == ':')
		{
			path = dup_chars(pathstr, curr_pos, c);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[c])
				break;
			curr_pos = c;
		}
		c++;
	}
	return (NULL);
}
