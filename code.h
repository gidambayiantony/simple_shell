#ifndef CODE_H
#define CODE_H

#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>


#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2


#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

extern char **environ;


/**
 * struct liststr - Definition of a singly linked list node
 * @num: Integer field within the node
 * @str: A character string contained in the node
 * @next: Pointer to the next node in the list
 */

typedef struct liststr
{
        int num;
        char *str;
        struct liststr *next;
} list_t;

/**
 * struct passinfo - Pseudo-argument for passing data into a function,
 * allowing a uniform prototype for a function pointer structure
 * @arg: A string generated from getline containing arguments
 * @argv: An array of strings generated from the argument
 * @path: A string representing the current command's path
 * @argc: Argument count
 * @line_count: Error count
 * @err_num: Error code for exit()
 * @linecount_flag: If set, count this line of input
 * @fname: Program filename
 * @env: Linked list, local copy of the environment variables
 * @environ: Modified copy of environment variables from the linked list 'env'
 * @history: History node
 * @alias: Alias node
 * @env_changed: Set to '1' if the environment was changed
 * @status: The return status of the last executed command
 * @cmd_buf: Address of a pointer to cmd_buf, set to '1' if chaining
 * @cmd_buf_type: CMD_type (||, &&, ;)
 * @readfd: The file descriptor from which to read line input
 * @histcount: History line number count
 */

typedef struct passinfo
{
        char *arg;
        char **argv;
        char *path;
        int argc;
        unsigned int line_count;
        int err_num;
        int linecount_flag;
        char *fname;
        list_t *env;
        list_t *history;
        list_t *alias;
        char **environ;
        int env_changed;
        int status;

        char **cmd_buf;
        int cmd_buf_type;
        int readuv;
        int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0 , 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
                0, 0, 0}


/**
 * struct builtin - Structure representing a built-in command and its related function
 * @type: Flag indicating the built-in command type
 * @func: Pointer to the associated function
 */

typedef struct builtin
{
	 char *type;
        int (*func)(info_t *);
} builtin_table;



int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);


int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);


int loophsh(char **);


void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);


int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);


char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);


char **strtow(char *, char *);
char **strtow2(char *, char);


char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);


int bfree(void **);


int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);


char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);


int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);


int _myhistory(info_t *);
int _myalias(info_t *);


ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);


void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);



int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);



char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);


list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);


size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);


char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);



#endif
