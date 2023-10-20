#include "code.h"

/**
 * input_buf - Buffer chained command.
 * @info: Parameter structure.
 * @buf: Buffer address.
 * @len: Buffer length.
 *
 * Return: Bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
    ssize_t y = 0;
    size_t len_p = 0;

    if (!*len) /* If nothing left in the buffer, fill it */
    {
        /*bfree((void **)info->cmd_buf);*/
        free(*buf);
        *buf = NULL;
        signal(SIGINT, sigintHandler);
#if USE_GETLINE
        y = getline(buf, &len_p, stdin);
#else
        y = _getline(info, buf, &len_p);
#endif
        if (y > 0)
        {
            if ((*buf)[y - 1] == '\n')
            {
                (*buf)[y - 1] = '\0'; /* Remove trailing newline */
                y--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);
            /* if (_strchr(*buf, ';')) is this a command chain? */
            {
                *len = y;
                info->cmd_buf = buf;
            }
        }
    }
    return (y);
}

/**
 * get_input - Get line minus newline.
 * @info: Parameter structure.
 *
 * Return: Bytes read.
 */
ssize_t get_input(info_t *info)
{
    static char *buf; /* The ';' command chain buffer */
    static size_t i, j, len;
    ssize_t y = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    y = input_buf(info, &buf, &len);
    if (y == -1) /* EOF */
        return (-1);
    if (len) /* We have commands left in the chain buffer */
    {
        j = i; /* Init a new iterator to the current buffer position */
        p = buf + i; /* Get a pointer for return */

        check_chain(info, buf, &j, i, len);
        while (j < len) /* Iterate to semicolon or end */
        {
            if (is_chain(info, buf, &j))
                break;
            j++;
        }

        i = j + 1; /* Increment past the nulled ';'' */
        if (i >= len) /* Reached the end of the buffer? */
        {
            i = len = 0; /* Reset position and length */
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p; /* Pass back a pointer to the current command position */
        return (_strlen(p)); /* Return the length of the current command */
    }

    *buf_p = buf; /* Else not a chain, pass back the buffer from _getline() */
    return (y); /* Return the length of the buffer from _getline() */
}

/**
 * read_buf - Read a buffer.
 * @info: Parameter structure.
 * @buf: Buffer.
 * @i: Size.
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
    ssize_t y = 0;

    if (*i)
        return (0);
    y = read(info->readfd, buf, READ_BUF_SIZE);
    if (y >= 0)
        *i = y;
    return (y);
}

/**
 * _getline - Get the next line of input from STDIN.
 * @info: Parameter structure.
 * @ptr: Pointer address to a buffer, preallocated or NULL.
 * @length: Size of the preallocated ptr buffer if not NULL.
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t y = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    y = read_buf(info, buf, &len);
    if (y == -1 || (y == 0 && len == 0))
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
 * sigintHandler - Block ctrl-C.
 * @sig_num: Signal number.
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}
