#include "shell.h"

void sig_handler(int sig);

/**
 * sig_handler - handles signal
 * @sig: the signal
 */

void sig_handler(int sig)
{
	char *shell_new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, shell_new_prompt, 3);
}

/**
 * execute - executes a cmd in a child process
 * @command_args: array of arguments for a command
 * @args_start: pointer to starting of command_args
 *
 * Return: exit value of last executed cmd
 */

int execute(char **command_args, char **args_start)
{
	pid_t child_process_id;
	char *cmd = command_args[0];
	int is_relative_path = 0, retu_status = 0, proc_status;

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		is_relative_path = 1;
		cmd = fetch_loc(cmd);
	}
	if (!cmd || (access(cmd, F_OK) == -1))
	{
		if (errno == EACCES)
			retu_status = (generate_err(command_args, 126));
		else
			retu_status = (generate_err(command_args, 127));
	}
	else
	{
		child_process_id = fork();
		if (child_process_id == -1)
		{
			if (is_relative_path)
				free(cmd);
			perror("Error child:");
			return (1);
		}
		if (child_process_id == 0)
		{
			execve(cmd, command_args, environ);
			if (errno == EACCES)
				retu_status = (generate_err(command_args, 126));
			envir_free();
			args_free(command_args, args_start);
			list_alias_free(alias_list);
			_exit(retu_status);
		}
		else
		{
			wait(&proc_status);
			retu_status = WEXITSTATUS(proc_status);
		}
	}
	if (is_relative_path)
		free(cmd);
	return (retu_status);
}
