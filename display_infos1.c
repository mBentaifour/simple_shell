#include "shell.h"

void displ_all_info(void);
void alias_displ_info(void);
void cd_displ_info(void);
void ex_displ_info(void);
void displ_info(void);

/**
* displ_all_info - shows all infos on shell
*/

void displ_all_info(void)
{
	char *info_ms = "Shellby\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
}

/**
* alias_displ_info - shows info about aliases
*/

void alias_displ_info(void)
{
	char *info_ms = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
}

/**
* cd_displ_info - shows infos about cd
*/

void cd_displ_info(void)
{
	char *info_ms = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "after a change of directory.\n";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
}

/**
* ex_displ_info - shows infos about exit
*/

void ex_displ_info(void)
{
	char *info_ms = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = " exit 0.\n";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
}

/**
* displ_info - shows infos about help
*/

void displ_info(void)
{
	char *info_ms = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
	info_ms = "builtin command.\n";
	write(STDOUT_FILENO, info_ms, _str_length(info_ms));
}
