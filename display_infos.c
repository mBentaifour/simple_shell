#include "shell.h"

void env_displ_info(void);
void setenv_displ_info(void);
void unsetenv_displ_info(void);
void his_displ_info(void);

/**
* env_displ_info - shows infos on shell
*/

void env_displ_info(void)
{
	char *info_ms = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
}

/**
* setenv_displ_info - shows infos on shell
*/

void setenv_displ_info(void)
{
	char *info_ms = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
}

/**
 * unsetenv_displ_info - shows infos on shell
 */

void unsetenv_displ_info(void)
{
	char *info_ms = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "message to stderr.\n";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
}
