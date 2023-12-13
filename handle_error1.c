#include "shell.h"

char *ex_126_err(char **cmd_arg);
char *ex_127_err(char **cmd_arg);

/**
 * ex_126_err - generates an error message 126
 * @cmd_arg: command
 *
 * Return: error message as ptr to char
 */
char *ex_126_err(char **cmd_arg)
{
	int length;
	char *err;
	char *str_his;

	str_his = custom_itoa(history_count);
	if (!str_his)
		return (NULL);

	length = _str_length(program_name) + _str_length(str_his) + _str_length(cmd_arg[0]) + 24;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(str_his);
		return (NULL);
	}

	_str_cpy(err, program_name);
	_str_cat(err, ": ");
	_str_cat(err, str_his);
	_str_cat(err, ": ");
	_str_cat(err, cmd_arg[0]);
	_str_cat(err, ": Permission denied\n");

	free(str_his);
	return (err);
}
/**
 * ex_127_err - genrates an error message 127
 * @cmd_arg: command
 *
 * Return: error message as ptr to char
 */
char *ex_127_err(char **cmd_arg)
{
	int length;
	char *err;
	char *str_his;

	str_his = custom_itoa(history_count);
	if (!str_his)
		return (NULL);

	length = _str_length(program_name) + _str_length(str_his) + _str_length(cmd_arg[0]) + 16;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(str_his);
		return (NULL);
	}

	_str_cpy(err, program_name);
	_str_cat(err, ": ");
	_str_cat(err, str_his);
	_str_cat(err, ": ");
	_str_cat(err, cmd_arg[0]);
	_str_cat(err, ": not found\n");

	free(str_his);
	return (err);
}
