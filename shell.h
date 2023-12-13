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
int history_count;
char *pgram_name;

/**
 * struct builtin_s - str type defining builtin commands
 * @built_cmd_name: builtin cmd name
 * @fun: pointer to builtin command
*/

typedef struct builtin_s
{
	char *built_cmd_name;
	int (*fun)(char **argv, char **start_of_args);
} builtin_t;

/**
 * struct list_s - struct type defining a linked list
 * @dir: the path of directory
 * @next: pointer to next node
*/

typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct alias_s - struct defining aliases
 * @name: alias name
 * @value: alias value
 * @next: pointer to next node
 */

typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

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

char *fetch_camdda(char *camdda_line, int *last_camdda_status);
int execute_cmd(char **camdda_args, char **start_of_args, int *last_camdda_status);
int cmd_run(char **camdda_args, char **start_of_args, int *last_camdda_status);
int process_args(int *last_camdda_status);
int validate_args(char **camdda_args);

void read_line(char **camdda, ssize_t mode);
void rep_var(char **camdda_args, int *last_camdda_status);
void args_free(char **last_camdda_status, char **start_of_args);
char **substitute_alias(char **camdda_args);

char **custom_strtok(char *camdda, char *c_deli);
void *custom_realloc(void *buff, unsigned int first_s, unsigned int second_s);
ssize_t custom_getline(char **buff_ptr, size_t *buff_size, FILE *stream);
char *custom_itoa(int n);
char *fetch_loc(char *camdda);
int execute(char **camdda_args, char **args_start);
list_t *fetch_dir_p(char *env_path);
void free_list(list_t *head);

int (*fetch_built(char *camdda))(char **camdda_args, char **start_of_args);
int exit_hsh(char **camdda_args, char **start_of_args);
int env_hsh(char **camdda_args, char __attribute__((__unused__)) **start_of_args);
int setenv_hsh(char **camdda_args, char __attribute__((__unused__)) **start_of_args);
int unsetenv_hsh(char **camdda_args, char __attribute__((__unused__)) **start_of_args);
int cd_hsh(char **camdda_args, char __attribute__((__unused__)) **start_of_args);
int alias_hsh(char **camdda_args, char __attribute__((__unused__)) **start_of_args);
int help_hsh(char **camdda_args, char __attribute__((__unused__)) **start_of_args);

char **custom_getenv(const char *var);
void envir_free(void);
char **_cpy_environement();

char *sec_cd_err(char **camdda_args);
char *sec_syn_err(char **camdda_args);
char *ex_126_err(char **camdda_args);
char *ex_127_err(char **camdda_args);
int generate_err(char **camdda_args, int error);
char *env_err(char **camdda_args);
char *first_err(char **camdda_args);
char *sec_ex_err(char **camdda_args);

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

int cmd_prcs(char *path_f, int *last_cmd_status);
#endif
