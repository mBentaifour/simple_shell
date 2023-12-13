#include "shell.h"

/**
 * fetch_loc - gets Location of a cmd
 * @cmd: command to get its location
 *
 * Return: path of cmd or NULL
 */
char *fetch_loc(char *cmd)
{
	list_t *list_dirs, *list_head;
	char **env_path, *t_path;
	struct stat st;

	env_path = custom_getenv("PATH");
	if (!env_path || !(*env_path))
		return (NULL);
	list_dirs = fetch_dir_p(*env_path + 5);
	list_head = list_dirs;
	while (list_dirs)
	{
		t_path = malloc(_str_length(list_dirs->dir) + _str_length(cmd) + 2);
		if (!t_path)
			return (NULL);
		_str_cpy(t_path, list_dirs->dir);
		_str_cat(t_path, "/");
		_str_cat(t_path, cmd);
		if (stat(t_path, &st) == 0)
		{
			free_list(list_head);
			return (t_path);
		}
		list_dirs = list_dirs->next;
		free(t_path);
	}
	free_list(list_head);
	return (NULL);
}

/**
 * copy_path - copies path
 * @env_path: the path
 *
 * Return: Copy of path
 */

char *copy_path(char *env_path)
{
	char *cp, *pwd;
	int index, len = 0;

	pwd = *(custom_getenv("PWD")) + 4;
	for (index = 0; env_path[index]; index++)
	{
		if (env_path[index] == ':')
		{
			if (env_path[index + 1] == ':' || index == 0 || env_path[index + 1] == '\0')
				len += _str_length(pwd) + 1;
			else
				len++;
		}
		else
			len++;
	}
	cp = malloc(sizeof(char) * (len + 1));
	if (!cp)
		return (NULL);
	cp[0] = '\0';
	for (index = 0; env_path[index]; index++)
	{
		if (env_path[index] == ':')
		{
			if (index == 0)
			{
				_str_cat(cp, pwd);
				_str_cat(cp, ":");
			}
			else if (env_path[index + 1] == ':' || env_path[index + 1] == '\0')
			{
				_str_cat(cp, ":");
				_str_cat(cp, pwd);
			}
			else
				_str_cat(cp, ":");
		}
		else
		{
			_str_n_cat(cp, &env_path[index], 1);
		}
	}
	return (cp);
}

/**
 * fetch_dir_p - splits path
 * @env_path: the path
 *
 * Return: pointer to path
 */

list_t *fetch_dir_p(char *env_path)
{
	char **list_dirs, *cp;
	int i;
	list_t *list_head = NULL;

	cp = copy_path(env_path);
	if (!cp)
		return (NULL);
	list_dirs = custom_strtok(cp, ":");
	free(cp);
	if (!list_dirs)
		return (NULL);
	for (i = 0; list_dirs[i]; i++)
	{
		if (append_node(&list_head, list_dirs[i]) == NULL)
		{
			free_list(list_head);
			free(list_dirs);
			return (NULL);
		}
	}
	free(list_dirs);
	return (list_head);
}
