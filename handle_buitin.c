#include "shell.h"

int (*fetch_built(char *cmd))(char **cmd_args, char **start_of_args);
int exit_hsh(char **cmd_args, char **start_of_args);
int cd_hsh(char **cmd_args, char __attribute__((__unused__)) **start_of_args);
int help_hsh(char **cmd_args, char __attribute__((__unused__)) **start_of_args);

/**
* fetch_built - gets builtin fun
* @cmd: command
*
* Return: pointer to fun
*/

int (*fetch_built(char *cmd))(char **cmd_args, char **start_of_args)
{
	builtin_t funcs[] = {
		{"exit", exit_hsh},
		{"env", env_shll},
		{"setenv", setenv_shll},
		{"unsetenv", unsetenv_shll},
		{"cd", cd_hsh},
		{"alias", alias_hsh},
		{"help", help_hsh},
		{NULL, NULL}};
	int index;

	for (index = 0; funcs[index].built_cmd_name; index++)
	{
		if (_str_cmp(funcs[index].built_cmd_name, cmd) == 0)
			break;
	}
	return (funcs[index].fun);
}

/**
* exit_shll - exists process
* @cmd_args: arguments
* @start_of_args: srating of arg
*
* Return: Satut value
*/

int exit_shll(char **cmd_args, char **start_of_args)
{
	unsigned int n = 0;
	unsigned int max = 1 << (sizeof(int) * 8 - 1);
	int num_length = 10;
	int index;

	if (cmd_args[0])
	{
		if (cmd_args[0][0] == '+')
		{
			index = 1;
			num_length++;
		}
		for (; cmd_args[0][index]; index++)
		{
			if (index <= num_length && cmd_args[0][index] >= '0' && cmd_args[0][index] <= '9')
				n = (n * 10) + (cmd_args[0][index] - '0');
			else
				return (generate_err(--cmd_args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (n > max - 1)
		return (generate_err(--cmd_args, 2));
	cmd_args -= 1;
	args_free(cmd_args, start_of_args);
	envir_free();
	list_alias_free(alias_list);
	exit(n);
}

/**
* cd_hsh - modifies dir
* @cmd_args: arguments
* @start_of_args: starting of args
*
* Return: 0
*/

int cd_hsh(char **cmd_args, char __attribute__((__unused__)) **start_of_args)
{
	char *pre_pwd = NULL, *pwd = NULL;
	char **inf_pa, *nl = "\n";
	struct stat dir;

	pre_pwd = getcwd(pre_pwd, 0);
	if (!pre_pwd)
		return (-1);

	if (cmd_args[0])
	{
		if (*(cmd_args[0]) == '-' || _str_cmp(cmd_args[0], "--") == 0)
		{
			if ((cmd_args[0][1] == '-' && cmd_args[0][2] == '\0') || cmd_args[0][1] == '\0')
				{
					if (custom_getenv("OLDPWD") != NULL)
						(chdir(*custom_getenv("OLDPWD") + 7));
				}
				else
				{
					free(pre_pwd);
					return (generate_err(cmd_args, 2));
				}
		}
		else
		{
			if (stat(cmd_args[0], &dir) == 0 && S_ISDIR(dir.st_mode) && ((dir.st_mode & S_IXUSR) != 0))
				chdir(cmd_args[0]);
			else
			{
				free(pre_pwd);
				return (generate_err(cmd_args, 2));
			}
		}
	}
	else
	{
		if (custom_getenv("HOME") != NULL)
			chdir(*(custom_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	inf_pa = malloc(sizeof(char *) * 2);
	if (!inf_pa)
		return (-1);

	inf_pa[0] = "OLDPWD";
	inf_pa[1] = pre_pwd;
	if (setenv_hsh(inf_pa, inf_pa) == -1)
		return (-1);

	inf_pa[0] = "PWD";
	inf_pa[1] = pwd;
	if (setenv_hsh(inf_pa, inf_pa) == -1)
		return (-1);
	if (cmd_args[0] && cmd_args[0][0] == '-' && cmd_args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _str_length(pwd));
		write(STDOUT_FILENO, nl, 1);
	}
	free(pre_pwd);
	free(pwd);
	free(inf_pa);
	return (0);
}

/**
* help_hsh - shows info on shell
* @cmd_args: arguments
* @start_of_args: starting of arg
*
* Return: 0 or -1
*/

int help_hsh(char **cmd_args, char __attribute__((__unused__)) **start_of_args)
{
	if (!cmd_args[0])
		displ_all_info();
	else if (_str_cmp(cmd_args[0], "alias") == 0)
		alias_displ_info();
	else if (_str_cmp(cmd_args[0], "cd") == 0)
		cd_displ_info();
	else if (_str_cmp(cmd_args[0], "exit") == 0)
		ex_displ_info();
	else if (_str_cmp(cmd_args[0], "env") == 0)
		env_displ_info();
	else if (_str_cmp(cmd_args[0], "setenv") == 0)
		setenv_displ_info();
	else if (_str_cmp(cmd_args[0], "unsetenv") == 0)
		unsetenv_displ_info();
	else if (_str_cmp(cmd_args[0], "help") == 0)
		displ_info();
	else
		write(STDERR_FILENO, program_name, _str_length(program_name));

	return (0);
}
