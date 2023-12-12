#include "shell.h"

/**
 * main - principal function to execut the Shell.
 * @argc: arguments count.
 * @argv: an array of pointers to the arguments.
 *
 * Return: returned value from the execution.
 */
int main(int argc, char *argv[])
{
	char *shell_prompt = "$ ", *line_break = "\n";
	int return_status = 0, execution_status;
	int *execution_status_ptr = &execution_status;

	program_name = argv[0];
	history_count = 1;
	alias_list = NULL;
	signal(SIGINT, sig_handler);
	*execution_status_ptr = 0;
	environ = _cpy_environement();
	if (!environ)
		exit(-100);
	if (argc != 1)
	{
		return_status = cmd_process(argv[1], execution_status_ptr);
		envir_free();
		list_alias_free(alias_list);
		return (*execution_status_ptr);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (return_status != END_OF_FILE && return_status != EXIT)
			return_status = process_args(execution_status_ptr);
		envir_free();
		list_alias_free(alias_list);
		return (*execution_status_ptr);
	}
	while (1)
	{
		write(STDOUT_FILENO, shell_prompt, 2);
		return_status = process_args(execution_status_ptr);
		if (return_status == END_OF_FILE || return_status == EXIT)
		{
			if (return_status == END_OF_FILE)
				write(STDOUT_FILENO, line_break, 1);
			envir_free();
			list_alias_free(alias_list);
			exit(*execution_status_ptr);
		}
	}
	envir_free();
	list_alias_free(alias_list);
	return (*execution_status_ptr);
}
