#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

/**
 * struct info_t - contains info needed for shell operation
 * @buffer: pointer to put buffer
 * @status: exit status
 * @@envp: pointer to env vars
 * @argv: pointer to arr of args passed to the shell
 * @arr_num: error no.
 */
typedef struct info_t
{
	char *buffer;
	char **argv;
	int err_num;
	int status;
	char **environ;
	int argc;
	list_t *env;
	list_t *alias;
	char *path;
	list_t *history;

	char **cmd_buf; /*pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_TYPE ||, &&, ; */
	int histcount;
	int readfd;
} info_t;

/**
 *struct builtin - contains a builtin string and related functtion
 *@func: the function
 *@type: the builtin command flag
 */
typedef struct builtin
{
	char *type;
	int(*func)(info_t *);
}

#define INFO_INT \
{NULL, NULL. NULL, 0,, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


/*maximum file path length*/
#define FILE_PATH_MAX_LEN 1024

/*maxmum no. of args to be passed to a cmd*/
#define MAX_COMMAND_ARGS 128

/*function prototype*/
int execute_command(char *command_with_args,
		char *program_name,
		int line_number);
void excute(char **args);
void free_args(char **args);
void print_args(int argc, char **argv);
void shell_loop(char *program_name);
void print_prompt(void);
char **tokenize_command(char *command_with_args,
		char *delimetre,
		int *num_args);
void handle_error(void);
extern int child_exit_status;
char *read_input(void);
int _execute(char **args, char *program_name, int line_number);
/*memory*/

/* toem_builtin.c */
int _myexit(info_t *);
int _myhelp(info_t *);
int _mycd(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
void signtHandler(int);
int _getline(info_t *, char **, size_t *);

/*toem_errors1.c */
int _erratoi(char *);
char *convert_number(long int, int, int);
void remove_comments(char *);
int print_d(int, int);
void print_error(info_t *, char *);

/*toem_builtin1.c */
int _myalias(info_t *);
int _myhistory(info_t *);

/*toem_atoi.c */
int _atoi(char *);
int is_delim(char, char *);
int isalpha(int);
int interactive(info_t *);

/*env prototypes*/
char **_split(char *str, char *delim);
char *_which(char *cmd);
char *_getenv(const char *env_var);
char *_find_command_path(char *cmd);
char *_strdup(char *str);

/* toem_exits.c */
char *_strncpy(char *, int);
char *_strchr(char *; char);
char *_strncat(char *, char *, int);
void exit_shell(void);

/* toem_getenv.c */
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *, char *);

/*function prototypes for string functions*/
int _strcmp(char *s1, char *s2);
int _strlen(const char *str);
int _putchar(char ch);
char *_strncopy(char *dest, const char *src, size_t num_chars);
void _put(char *s);
char *starts_with(const char *, const char *);

/*arr of strings for env variables*/
extern char **environ;

/*prototype to printf current env*/
int print_env(const char *kepp_var);

/*toem_environ.c */
int populate_env_list(info_t *);
char *_getenv(info_t *, const char *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int myenv(info_t *);

#endif /*SHELL_H*/
