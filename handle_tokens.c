#include "shell.h"

/**
 * len_token - Get  length of given token
 * @str: searched string
 * @c_deli: delimeter of string
 *
 * Return: position of delimeter as integer
 */
int len_token(char *str, char *c_deli)
{
	int length = 0;
	int i = 0;

	while (*(str + i) && *(str + i) != *c_deli)
	{
		length++;
		i++;
	}
	return (length);
}

/**
 * token_counter - count of delimiter in string
 * @str: string looked in
 * @c_deli: delimeter
 * Return: count of delimiter in a string
 */
int token_counter(char *str, char *c_deli)
{
	int i;
	int length = 0;
	int tokens = 0;

	for (i = 0; *(str + i); i++)
		length++;

	for (i = 0; i < length; i++)
	{
		if (*(str + i) != *c_deli)
		{
			tokens++;
			i += len_token(str + i, c_deli);
		}
	}

	return (tokens);
}

/**
 * custom_strtok - parses a string
 * @cmd: string
 * @c_deli: delimeter character
 *
 * Return: ptr to tokens array
 */
char **custom_strtok(char *cmd, char *c_deli)
{
	int index = 0;
	int count_tokens;
	int index_token;
	int count_l;
	int index_l;
	char **tokens_arr;

	count_tokens = token_counter(cmd, c_deli);
	if (count_tokens == 0)
		return (NULL);
	tokens_arr = malloc(sizeof(char *) * (count_tokens + 2));
	if (!tokens_arr)
		return (NULL);
	for (index_token = 0; index_token < count_tokens; index_token++)
	{
		while (cmd[index] == *c_deli)
			index++;

		count_l = len_token(cmd + index, c_deli);

		tokens_arr[index_token] = malloc(sizeof(char) * (count_l + 1));
		if (!tokens_arr[index_token])
		{
			for (index -= 1; index >= 0; index--)
				free(tokens_arr[index]);
			free(tokens_arr);
			return (NULL);
		}

		for (index_l = 0; index_l < count_l; index_l++)
		{
			tokens_arr[index_token][index_l] = cmd[index];
			index++;
		}

		tokens_arr[index_token][index_l] = '\0';
	}
	tokens_arr[index_token] = NULL;
	tokens_arr[index_token + 1] = NULL;
	return (tokens_arr);
}
