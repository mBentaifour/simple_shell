#include "shell.h"

int env_shll(char **cmd_args, char __attribute__((__unused__)) **start_of_args);
int setenv_shll(char **cmd_args, char __attribute__((__unused__)) **start_of_args);
int unsetenv_shll(char **cmd_args, char __attribute__((__unused__)) **start_of_args);

/**
* env_shll - show envirement
* @cmd_args: Arguments
* @start_of_args: starting of arguments
*
* Return: 0 or -1
*/

int env_shll(char **cmd_args, char __attribute__((__unused__)) **start_of_args)
{
	char new_c = '\n';
	int i;

	if (!environ)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _str_length(environ[i]));
		write(STDOUT_FILENO, &new_c, 1);
	}

	(void)cmd_args;
	return (0);
}

/**
* setenv_shll - appends to the envirement variables
* @cmd_args: arguments
* @start_of_args: starting of arguments
* Return: 0 or -1
*/

int setenv_shll(char **cmd_args, char __attribute__((__unused__)) **start_of_args)
{
	size_t s;
	int i;
	char **ptr_env_v = NULL, **next_env, *next_val;

	if (!cmd_args[0] || !cmd_args[1])
		return (generate_err(cmd_args, -1));

	next_val = malloc(_str_length(cmd_args[0]) + 1 + _str_length(cmd_args[1]) + 1);
	if (!next_val)
		return (generate_err(cmd_args, -1));
	_str_cpy(next_val, cmd_args[0]);
	_str_cat(next_val, "=");
	_str_cat(next_val, cmd_args[1]);

	ptr_env_v = custom_getenv(cmd_args[0]);
	if (ptr_env_v)
	{
		free(*ptr_env_v);
		*ptr_env_v = next_val;
		return (0);
	}

	for (s = 0; environ[s]; s++)
		;

	next_env = malloc(sizeof(char *) * (s + 2));
	if (!next_env)
	{
		free(next_val);
		return (generate_err(cmd_args, -1));
	}

	for (i = 0; environ[i]; i++)
		next_env[i] = environ[i];

	free(environ);
	environ = next_env;
	environ[i] = next_val;
	environ[i + 1] = NULL;

	return (0);
}

/**
* unsetenv_shll - removes envirement variables
* @cmd_args: arguments
* @start_of_args: starting of arguments
* Return: 0 or -1
*/

int unsetenv_shll(char **cmd_args, char __attribute__((__unused__)) **start_of_args)
{
	size_t s;
	int i, ind2;
	char **ptr_env_v, **next_env;

	if (!cmd_args[0])
		return (generate_err(cmd_args, -1));
	ptr_env_v = custom_getenv(cmd_args[0]);
	if (!ptr_env_v)
		return (0);

	for (s = 0; environ[s]; s++)
		;

	next_env = malloc(sizeof(char *) * s);
	if (!next_env)
		return (generate_err(cmd_args, -1));

	for (i = 0, ind2 = 0; environ[i]; i++)
	{
		if (*ptr_env_v == environ[i])
		{
			free(*ptr_env_v);
			continue;
		}
		next_env[ind2] = environ[i];
		ind2++;
	}
	free(environ);
	environ = next_env;
	environ[s - 1] = NULL;

	return (0);
}
