#include "shell.h"

/**
 * check_operator - check logical operator for a cmd passed as arg
 * @cmd: command to  check
 * @fresh_length: The length
 */
void check_operator(char *cmd, ssize_t *fresh_length)
{
	char next;
	char cursor;
	char pre;

	cursor = *cmd;
	next = *(cmd + 1);
	pre = *(cmd - 1);
	if (cursor == '&')
	{
		if (next == '&' && pre != ' ')
			(*fresh_length)++;
		else if (pre == '&' && next != ' ')
			(*fresh_length)++;
	}
	else if (cursor == '|')
	{
		if (next == '|' && pre != ' ')
			(*fresh_length)++;
		else if (pre == '|' && next != ' ')
			(*fresh_length)++;
	}
}

/**
 * fetch_length - fetch a new length of a cmd passed as arg
 * @cmd: the command to fetch
 * Return: Length of command
 */
ssize_t fetch_length(char *cmd)
{
	char cursor, next;
	size_t index;
	ssize_t fresh_length = 0;

	for (index = 0; cmd[index]; index++)
	{
		cursor = cmd[index];
		next = cmd[index + 1];
		if (cursor == '#')
		{
			if (index == 0 || cmd[index - 1] == ' ')
			{
				cmd[index] = '\0';
				break;
			}
		}
		else if (index != 0)
		{
			if (cursor == ';')
			{
				if (next == ';' && cmd[index - 1] != ' ' && cmd[index - 1] != ';')
				{
					fresh_length += 2;
					continue;
				}
				else if (cmd[index - 1] == ';' && next != ' ')
				{
					fresh_length += 2;
					continue;
				}
				if (cmd[index - 1] != ' ')
					fresh_length++;
				if (next != ' ')
					fresh_length++;
			}
			else
				check_operator(&cmd[index], &fresh_length);
		}
		else if (cursor == ';')
		{
			if (index != 0 && cmd[index - 1] != ' ')
				fresh_length++;
			if (next != ' ' && next != ';')
				fresh_length++;
		}
		fresh_length++;
	}
	return (fresh_length);
}
/**
 * read_line - Split line
 * @cmd: line to proced
 * @mode: line length
 */
void read_line(char **cmd, ssize_t line_len)
{
	char pre, cur, next;
	char *pre_cmd, *nex_cmd;
	ssize_t fresh_length;
	size_t index, j;

	fresh_length = fetch_length(*cmd);
	if (fresh_length == line_len - 1)
		return;
	nex_cmd = malloc(fresh_length + 1);
	if (!nex_cmd)
		return;
	j = 0;
	pre_cmd = *cmd;
	for (index = 0; pre_cmd[index]; index++)
	{
		cur = pre_cmd[index];
		next = pre_cmd[index + 1];
		if (index != 0)
		{
			pre = pre_cmd[index - 1];
			if (cur == ';')
			{
				if (next == ';' && pre != ' ' && pre != ';')
				{
					nex_cmd[j++] = ' ';
					nex_cmd[j++] = ';';
					continue;
				}
				else if (pre == ';' && next != ' ')
				{
					nex_cmd[j++] = ';';
					nex_cmd[j++] = ' ';
					continue;
				}
				if (pre != ' ')
					nex_cmd[j++] = ' ';
				nex_cmd[j++] = ';';
				if (next != ' ')
					nex_cmd[j++] = ' ';
				continue;
			}
			else if (cur == '&')
			{
				if (next == '&' && pre != ' ')
					nex_cmd[j++] = ' ';
				else if (pre == '&' && next != ' ')
				{
					nex_cmd[j++] = '&';
					nex_cmd[j++] = ' ';
					continue;
				}
			}
			else if (cur == '|')
			{
				if (next == '|' && pre != ' ')
					nex_cmd[j++]  = ' ';
				else if (pre == '|' && next != ' ')
				{
					nex_cmd[j++] = '|';
					nex_cmd[j++] = ' ';
					continue;
				}
			}
		}
		else if (cur == ';')
		{
			if (index != 0 && pre_cmd[index - 1] != ' ')
				nex_cmd[j++] = ' ';
			nex_cmd[j++] = ';';
			if (next != ' ' && next != ';')
				nex_cmd[j++] = ' ';
			continue;
		}
		nex_cmd[j++] = pre_cmd[index];
	}
	nex_cmd[j] = '\0';
	free(*cmd);
	*cmd = nex_cmd;
}
