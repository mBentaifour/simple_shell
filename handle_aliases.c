#include "shell.h"

int alias_hsh(char **cmd_args, char __attribute__((__unused__)) **start_of_args);
void put_alias(char *name_al, char *value);
void al_print(alias_t *alias);

/**
* alias_hsh - prints aliases
* @cmd_args: command line args
* @start_of_args: fisrt art of cmd_args
*
* Return: 0 or -1
*/

int alias_hsh(char **cmd_args, char __attribute__((__unused__)) **start_of_args)
{
	int index, val_retu = 0;
	alias_t *t = alias_list;
	char *curr_val;

	if (!cmd_args[0])
	{
		while (t)
		{
			al_print(t);
			t = t->next;
		}
		return (val_retu);
	}
	for (index = 0; cmd_args[index]; index++)
	{
		t = alias_list;
		curr_val = _str_chr(cmd_args[index], '=');
		if (!curr_val)
		{
			while (t)
			{
				if (_str_cmp(cmd_args[index], t->name) == 0)
				{
					al_print(t);
					break;
				}
				t = t->next;
			}
			if (!t)
				val_retu = generate_err(cmd_args + index, 1);
		}
		else
			put_alias(cmd_args[index], curr_val);
	}
	return (val_retu);
}

/**
* put_alias - sets alias
* @name_al: aliase name
* @value: a alias value
*/

void put_alias(char *name_al, char *value)
{
	int length;
	int j, k;
	char *next_val;
	alias_t *t = alias_list;

	*value = '\0';
	value++;
	length = _str_length(value) - _str_spn(value, "'\"");
	next_val = malloc(sizeof(char) * (length + 1));
	if (!next_val)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			next_val[k++] = value[j];
	}
	next_val[k] = '\0';
	while (t)
	{
		if (_str_cmp(name_al, t->name) == 0)
		{
			free(t->value);
			t->value = next_val;
			break;
		}
		t = t->next;
	}
	if (!t)
		append_alias(&alias_list, name_al, next_val);
}

/**
* al_print - prints alias
* @alias: alias ptr
*/

void al_print(alias_t *alias)
{
	char *str_al;
	int length = _str_length(alias->name) + _str_length(alias->value) + 4;

	str_al = malloc(sizeof(char) * (length + 1));
	if (!str_al)
		return;
	_str_cpy(str_al, alias->name);
	_str_cat(str_al, "='");
	_str_cat(str_al, alias->value);
	_str_cat(str_al, "'\n");

	write(STDOUT_FILENO, str_al, length);
	free(str_al);
}

/**
* substitute_alias - replaces args with aliases
* @cmd_args: array of pointers args
*
* Return: a pointer to pointer of array of args
*/

char **substitute_alias(char **cmd_args)
{
	int index;
	alias_t *t;
	char *next_val;

	if (_str_cmp(cmd_args[0], "alias") == 0)
		return (cmd_args);
	for (index = 0; cmd_args[index]; index++)
	{
		t = alias_list;
		while (t)
		{
			if (_str_cmp(cmd_args[index], t->name) == 0)
			{
				next_val = malloc(sizeof(char) * (_str_length(t->value) + 1));
				if (!next_val)
				{
					args_free(cmd_args, cmd_args);
					return (NULL);
				}
				_str_cpy(next_val, t->value);
				free(cmd_args[index]);
				cmd_args[index] = next_val;
				index--;
				break;
				}
				t = t->next;
		}
	}

		return (cmd_args);
}
