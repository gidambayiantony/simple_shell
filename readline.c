#include "code.h"
/**
 * input_Buf - Buff chain command
 * @info: param structure
 * @buf:  Buff address
 * @len:  Buff address
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t g = 0;
	size_t len_p = 0;

	if (!*len) 
	{
	
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		g = getline(buf, &len_p, stdin);

		g = _getline(info, buf, &len_p);

		if (g > 0)
		{
			if ((*buf)[g - 1] == '\n')
			{
				(*buf)[g - 1] = '\0'; /* remove trailing newline */
				g--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			
			{
				*len = g;
				info->cmd_buf = buf;
			}
		}
	}
	return (g);
}

/**
 * get_input - access line minus newline
 * @info: parram structure
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; 
	static size_t i, j, len;
	ssize_t g = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	g = input_buf(info, &buf, &len);
	if (g == -1) /* EOF */
		return (-1);
	if (len) 
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (g); /* return length of buffer from _getline() */
}

/**
 * read_buf - rd buff
 * @info: param structure
 * @buf: buff
 * @i: size
 *
 * Return: g
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t g = 0;

	if (*i)
		return (0);
	g = read(info->readuv, buf, READ_BUF_SIZE);
	if (g >= 0)
		*i = g;
	return (g);
}

/**
 * _getline - access next line  input from STDIN
 * @info: param structure
 * @ptr: ptr address to buff, preallocated or NULL
 * @length: size of the preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t g = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	g = read_buf(info, buf, &len);
	if (g == -1 || (g == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Block contrl-C
 * @sig_num:  no
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

