#include "shell.h"

/**
 * main - main function of shell program
 * @argc: number of arguments
 * @argv: array of pointers to arguments
 *
 * Return: returned from last executed command
 */
int main(int argc, char *argv[])
{
	char *shell_prompt = "$ ";
	char *line_break = "\n";
	int retu_status = 0;
	int execution_status;
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
		retu_status = cmd_process(argv[1], execution_status_ptr);
		envir_free();
		list_alias_free(alias_list);
		return (*execution_status_ptr);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (retu_status != END_OF_FILE && retu_status != EXIT)
			retu_status = process_args(execution_status_ptr);
		envir_free();
		list_alias_free(alias_list);
		return (*execution_status_ptr);
	}
	while (1)
	{
		write(STDOUT_FILENO, shell_prompt, 2);
		retu_status = process_args(execution_status_ptr);
		if (retu_status == END_OF_FILE || retu_status == EXIT)
		{
			if (retu_status == END_OF_FILE)
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
