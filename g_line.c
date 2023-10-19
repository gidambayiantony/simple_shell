#include "code.h"

/**
 * input_buf - Store chained commands in a buffer
 * @info: Parameter structure
 * @buf: Buffer address
 * @len: Buffer length
 *
 * Return: Number of bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t bytes_read = 0;
	size_t len_p = 0;

	if (!*len) 
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytes_read = getline(buf, &len_p, stdin);
#else
		bytes_read = _getline(info, buf, &len_p);
#endif
		if (bytes_read > 0)
		{
			if ((*buf)[bytes_read - 1] == '\n')
			{
				(*buf)[bytes_read - 1] = '\0'; 
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			*len = bytes_read;
			info->cmd_buf = buf;
		}
	}
	return bytes_read;
}

/**
 * get_input - Retrieve a line without the newline character
 * @info: Parameter structure
 *
 * Return: Number of bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buf; 
	static size_t h, v, len;
	ssize_t bytes_read = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	bytes_read = input_buf(info, &buf, &len);
	if (bytes_read == -1) 
		return -1;
	if (len) 
	{
		v = h; 
		while (v < len) 
		{
			if (is_chain(info, buf, &v))
				break;
			v++;
		}
		h = v + 1; 
		if (h >= len) 
		{
			h = len = 0; 
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = buf; 
		return _strlen(*buf_p); 
	}

	*buf_p = buf; 
	return bytes_read; 
}

/**
 * read_buf - Read data from a buffer
 * @info: Parameter structure
 * @buf: Buffer
 * @i: Size
 *
 * Return: The number of bytes read
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t bytes_read = 0;

	if (*i)
		return 0;
	bytes_read = read(info->readuv, buf, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*i = bytes_read;
	return bytes_read;
}

/**
 * _getline - Get the next line of input from STDIN
 * @info: Parameter structure
 * @ptr: Pointer address to a buffer, preallocated or NULL
 * @length: Size of the preallocated ptr buffer if not NULL
 *
 * Return: The number of bytes read
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t h, len;
	size_t e;
	ssize_t bytes_read = 0, m = 0;
	char *p = NULL, *new_p = NULL, *c;

	q = *ptr;
	if (q && length)
		m = *length;
	if (h == len)
		h = len = 0;

	bytes_read = read_buf(info, buf, &len);
	if (bytes_read == -1 || (bytes_read == 0 && len == 0))
		return -1;

	w = _strchr(buf + h, '\n');
	f = w ? 1 + (unsigned int)(w - buf) : len;
	new_p = _realloc(q, m, m ? m + f : f + 1);
	if (!new_p) 
		return (q ? free(q), -1 : -1);

	if (m)
		_strncat(new_p, buf + h, f - h);
	else
		_strncpy(new_p, buf + h, f - h + 1);

	m += f - h;
	h = f;
	q = new_p;

	if (length)
		*length = m;
	*ptr = q;
	return m;
}

/**
 * sigintHandler - Block the Ctrl-C signal
 * @sig_num: The signal number
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
