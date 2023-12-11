#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define END_OF_FILE -2
#define EXIT -3

extern char **environ;
int count_of_history;
char *program_name;

/**
 * struct builtin_s - Struct type defining builtin commands
 * @built_cmd_name: Builtin cmd name
 * @fun: Pointer to the builtin command
*/

typedef struct builtin_s
{
	char *built_cmd_name;
	int (*fun)(char **command_arguments, char **start_of_args);
}builtin_t;

/**
 * struct list_s - Struct type defining a linked list
 * @dir: The path of the directory
 * @next: Pointer to the next node
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
}list_t;

/**
 * struct alias_s - Struct defining aliases
 * @name: Alias's name
 * @value: Alias's value
 * @next: Pointer to the next node
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
}alias_t;

alias_t *alias_list;

void sig_handler(int sig);

char *_str_cat(char *dest_str, const char *src_str);
int _str_cmp(char *str1, char *str2);
int _str_length(const char *str);
char *_str_chr(char *str, char character);
char *_str_cpy(char *dest_str, const char *src_str);
char *_str_n_cat(char *dest_str, const char *src_str, size_t num);
int _str_spn(char *str, char *pref);
int _str_n_cmp(const char *str1, const char *str2, size_t num);

char *fetch_cmd(char *command_line, int *last_command_status);
int execute_cmd(char **command_arguments, char **start_of_args, int *last_command_status);
int cmd_run(char **command_arguments, char **start_of_args, int *last_command_status);
int process_args(int *last_command_status);
int validate_args(char **command_arguments);

void read_line(char **cmd, ssize_t mode);
void rep_var(char **command_arguments, int *last_command_status);
void args_free(char **last_command_status, char **start_of_args);
char **substitute_alias(char **command_arguments);

char **custom_strtok(char *cmd, char *c_deli);
void *custom_realloc(void *buff, unsigned int first_s, unsigned int second_s);
ssize_t custom_getline(char **buff_ptr, size_t *buff_size, FILE *stream);
char *custom_itoa(int n);
char *fetch_loc(char *cmd);
int execute(char **command_arguments, char **args_start);
list_t *fetch_dir_p(char *env_path);
void free_list(list_t *head);

int (*fetch_built(char *cmd))(char **command_arguments, char **start_of_args);
int exit_hsh(char **command_arguments, char **start_of_args);
int env_hsh(char **command_arguments, char __attribute__((__unused__)) **start_of_args);
int setenv_hsh(char **command_arguments, char __attribute__((__unused__)) **start_of_args);
int unsetenv_hsh(char **command_arguments, char __attribute__((__unused__)) **start_of_args);
int cd_hsh(char **command_arguments, char __attribute__((__unused__)) **start_of_args);
int alias_hsh(char **command_arguments, char __attribute__((__unused__)) **start_of_args);
int help_hsh(char **command_arguments, char __attribute__((__unused__)) **start_of_args);

char **custom_getenv(const char *var);
void envir_free(void);
char **_cpy_environement();

char *sec_cd_err(char **command_arguments);
char *sec_syn_err(char **command_arguments);
char *ex_126_err(char **command_arguments);
char *ex_127_err(char **command_arguments);
int generate_err(char **command_arguments, int error);
char *env_err(char **command_arguments);
char *first_err(char **command_arguments);
char *sec_ex_err(char **command_arguments);

alias_t *append_alias(alias_t **first_node, char *alias_name, char *alias_value);

list_t *append_node(list_t **first_node, char *dir);
void free_list(list_t *head);
void list_alias_free(alias_t *first_node);

void ex_displ_info(void);
void displ_info(void);
void env_displ_info(void);
void setenv_displ_info(void);
void unsetenv_displ_info(void);
void his_displ_info(void);
void displ_all_info(void);
void alias_displ_info(void);
void cd_displ_info(void);

int cmd_process(char *path_f, int *last_command_status);
#endif
