#include "shell.h"

/**
 * is_exist - check existence of file
 * @path_f: file path
 *
 * Return: always exit code 127
 */

int is_exist(char *path_f)
{
	int length;
	char *str_his;
	char *buff_err;

	str_his = custom_itoa(history_count);
	if (!str_his)
		return (127);
	length = _str_length(program_name) + _str_length(str_his) + _str_length(path_f) + 16;
	buff_err = malloc(sizeof(char) * (length + 1));
	if (!buff_err)
	{
		free(str_his);
		return (127);
	}
	_str_cpy(buff_err, program_name);
	_str_cat(buff_err, ": ");
	_str_cat(buff_err, str_his);
	_str_cat(buff_err, ": Can't open ");
	_str_cat(buff_err, path_f);
	_str_cat(buff_err, "\n");
	free(str_his);
	write(STDERR_FILENO, buff_err, length);
	free(buff_err);

	return (127);
}

/**
 * cmd_process - processes command
 * @path_f: a file path
 * @last_cmd_status: value of last executed cmd
 *
 * Return: last cmd value or 127 if it fails
 */

int cmd_process(char *path_f, int *last_cmd_status)
{
	char *line, **args, **start_of_args;
	char buff[120];
	ssize_t fd, bytes_read, index;
	int val_retu;
	unsigned int n = 0;
	unsigned int first_s = 120;

	history_count = 0;
	fd = open(path_f, O_RDONLY);
	if (fd == -1)
	{
		*last_cmd_status = is_exist(path_f);
		return (*last_cmd_status);
	}
	line = malloc(sizeof(char) * first_s);
	if (!line)
		return (-1);
	do {
		bytes_read = read(fd, buff, 119);
		if (bytes_read == 0 && n == 0)
			return (*last_cmd_status);
		buff[bytes_read] = '\0';
		n += bytes_read;
		line = custom_realloc(line, first_s, n);
		_str_cat(line, buff);
		first_s = n;
	} while (bytes_read);
	for (index = 0; line[index] == '\n'; index++)
		line[index] = ' ';
	for (; index < n; index++)
	{
		if (line[index] == '\n')
		{
			line[index] = ';';
			for (index += 1; index < n && line[index] == '\n'; index++)
				line[index] = ' ';
		}
	}
	rep_var(&line, last_cmd_status);
	read_line(&line, n);
	args = custom_strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (validate_args(args) != 0)
	{
		*last_cmd_status = 2;
		args_free(args, args);
		return (*last_cmd_status);
	}
	start_of_args = args;

	for (index = 0; args[index]; index++)
	{
		if (_str_n_cmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			val_retu = execute_cmd(args, start_of_args, last_cmd_status);
			args = &args[++index];
			index = 0;
		}
	}

	val_retu = execute_cmd(args, start_of_args, last_cmd_status);
	free(start_of_args);
	return (val_retu);
}
