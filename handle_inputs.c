#include "shell.h"

/**
 * fetch_cmd - fetchs a command line from end user
 * @cmd_line: buffer to store the command line
 * @last_cmd_status: a pointer to returned
 * value of last executed command
 *
 * Return: stored command or NULL
 */

char *fetch_cmd(char *cmd_line, int *last_cmd_status)
{
	char *prompt = "$ ";
	size_t buffer_size = 0;
	ssize_t bytes_read;

	if (cmd_line)
		free(cmd_line);
	bytes_read = custom_getline(&cmd_line, &buffer_size, STDIN_FILENO);
	if (bytes_read == -1)
		return (NULL);
	if (bytes_read == 1)
	{
		history_count++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (fetch_cmd(cmd_line, last_cmd_status));
	}
	cmd_line[bytes_read - 1] = '\0';
	rep_var(&cmd_line, last_cmd_status);
	read_line(&cmd_line, bytes_read);
	return (cmd_line);
}

/**
 * execute_cmd - executes commands
 * @cmd_args: array of args
 * @start_of_args: pointer to start of cmd_args
 * @last_cmd_status: return value of parent process
 *
 * Return: value returned from last executed command
 */

int execute_cmd(char **cmd_args, char **start_of_args, int *last_cmd_status)
{
	int index;
	int ret_status;

	if (!cmd_args[0])
		return (*last_cmd_status);
	for (index = 0; cmd_args[index]; index++)
	{
		if (_str_n_cmp(cmd_args[index], "||", 2) == 0)
		{
			free(cmd_args[index]);
			cmd_args[index] = NULL;
			cmd_args = substitute_alias(cmd_args);
			ret_status = cmd_run(cmd_args, start_of_args, last_cmd_status);
			if (*last_cmd_status != 0)
			{
				cmd_args = &cmd_args[++index];
				index = 0;
			}
			else
			{
				for (index++; cmd_args[index]; index++)
					free(cmd_args[index]);
				return (ret_status);
			}
		}
		else if (_str_n_cmp(cmd_args[index], "&&", 2) == 0)
		{
			free(cmd_args[index]);
			cmd_args[index] = NULL;
			cmd_args = substitute_alias(cmd_args);
			ret_status = cmd_run(cmd_args, start_of_args, last_cmd_status);
			if (*last_cmd_status == 0)
			{
				cmd_args = &cmd_args[++index];
				index = 0;
			}
			else
			{
				for (index++; cmd_args[index]; index++)
					free(cmd_args[index]);
				return (ret_status);
			}
		}
	}
	cmd_args = substitute_alias(cmd_args);
	ret_status = cmd_run(cmd_args, start_of_args, last_cmd_status);
	return (ret_status);
}

/**
 * cmd_run - invoke command
 * @cmd_args: array of args
 * @start_of_args: pointer to start of cmd_args
 * @last_cmd_status: return value of parent process
 *
 * Return: value of last exec cmd
 */

int cmd_run(char **cmd_args, char **start_of_args, int *last_cmd_status)
{
	int index;
	int ret_status;
	int (*builtin)(char **cmd_args, char **start_of_args);

	builtin = fetch_built(cmd_args[0]);
	if (builtin)
	{
		ret_status = builtin(cmd_args + 1, start_of_args);
		if (ret_status != EXIT)
			*last_cmd_status = ret_status;
	}
	else
	{
		*last_cmd_status = execute(cmd_args, start_of_args);
		ret_status = *last_cmd_status;
	}
	history_count++;
	for (index = 0; cmd_args[index]; index++)
		free(cmd_args[index]);
	return (ret_status);
}

/**
 * process_args - fetch and invoke execution of a command
 * @last_cmd_status: value returned from parent process
 *
 * Return: exit value of last executed command or EOF
 */

int process_args(int *last_cmd_status)
{
	int index;
	int ret_status = 0;
	char **cmd_args, *cmd_line = NULL, **start_of_args;

	cmd_line = fetch_cmd(cmd_line, last_cmd_status);
	if (!cmd_line)
		return (END_OF_FILE);
	cmd_args = custom_strtok(cmd_line, " ");
	free(cmd_line);
	if (!cmd_args)
		return (ret_status);
	if (validate_args(cmd_args) != 0)
	{
		*last_cmd_status = 2;
		args_free(cmd_args, cmd_args);
		return (*last_cmd_status);
	}
	start_of_args = cmd_args;
	for (index = 0; cmd_args[index]; index++)
	{
		if (_str_n_cmp(cmd_args[index], ";", 1) == 0)
		{
			free(cmd_args[index]);
			cmd_args[index] = NULL;
			ret_status = execute_cmd(cmd_args, start_of_args, last_cmd_status);
			cmd_args = &cmd_args[++index];
			index = 0;
		}
	}
	if (cmd_args)
		ret_status = execute_cmd(cmd_args, start_of_args, last_cmd_status);
	free(start_of_args);
	return (ret_status);
}

/**
 * validate_args - validates if there are any ';', ';;', '&&', or '||'
 * @cmd_args: a pointer to parsed commands
 *
 * Return: 0 or 2 - If a ';', '&&', or '||' is placed in a place
 */

int validate_args(char **cmd_args)
{
	char *current_arg, *next_arg;
	size_t index;

	for (index = 0; cmd_args[index]; index++)
	{
		current_arg = cmd_args[index];
		if (current_arg[0] == ';' || current_arg[0] == '&' || current_arg[0] == '|')
		{
			if (index == 0 || current_arg[1] == ';')
				return (generate_err(&cmd_args[index], 2));
			next_arg = cmd_args[index + 1];
			if (next_arg && (next_arg[0] == ';' || next_arg[0] == '&' || next_arg[0] == '|'))
				return (generate_err(&cmd_args[index + 1], 2));
		}
	}
	return (0);
}
