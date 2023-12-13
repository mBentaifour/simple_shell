#include "shell.h"

int length_counter(int n);
char *custom_itoa(int n);
int generate_err(char **cmd_arg, int error);

/**
* length_counter - counts a number length
* @n: countered number
*
* Return: length of number
*/

int length_counter(int n)
{
	int length = 1;
	unsigned int new_num;

	if (n < 0)
	{
		length++;
		new_num = n * -1;
	}
	else
	{
		new_num = n;
	}
	while (new_num > 9)
	{
		length++;
		new_num /= 10;
	}

	return (length);
}

/**
* custom_itoa - converts int to str
* @n: number
*
* Return: the str
*/

char *custom_itoa(int n)
{
	char *str_b;
	unsigned int new_num;
	int length = length_counter(n);

	str_b = malloc(sizeof(char) * (length + 1));
	if (!str_b)
		return (NULL);

	str_b[length] = '\0';

	if (n < 0)
	{
		new_num = n * -1;
		str_b[0] = '-';
	}
	else
	{
		new_num = n;
	}

	length--;
	do {
		str_b[length] = (new_num % 10) + '0';
		new_num /= 10;
		length--;
	} while (new_num > 0);

	return (str_b);
}

/**
* generate_err - generates error
* @cmd_arg: an array of arguments
* @error: value error
*
* Return: value error
*/

int generate_err(char **cmd_arg, int error)
{
	char *new_err;

	switch (error)
	{
		case -1:
				new_err = env_err(cmd_arg);
				break;
		case 1:
				new_err = first_err(cmd_arg);
				break;
		case 2:
				if (*(cmd_arg[0]) == 'e')
					new_err = sec_ex_err(++cmd_arg);
				else if (cmd_arg[0][0] == ';' || cmd_arg[0][0] == '&' || cmd_arg[0][0] == '|')
					new_err = sec_syn_err(cmd_arg);
				else
					new_err = sec_cd_err(cmd_arg);
				break;
		case 126:
				new_err = ex_126_err(cmd_arg);
				break;
		case 127:
				new_err = ex_127_err(cmd_arg);
				break;
	}
	write(STDERR_FILENO, new_err, _str_length(new_err));

	if (new_err)
		free(new_err);
	return (error);
}
