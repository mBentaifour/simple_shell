#include "shell.h"

/**
 * append_alias - add a alias to the end of a link list passed as arg
 * @first_node: ptr to the first alias
 * @alias_name: name of new alias
 * @alias_value: data of the new alias
 *
 * Return: ptr to the new alias or NULL
 */
alias_t *append_alias(alias_t **first_node, char *alias_name, char *alias_value)
{
	alias_t *tail;
	alias_t *n_node = malloc(sizeof(alias_t));

	if (!n_node)
		return (NULL);

	n_node->next = NULL;
	n_node->name = malloc(sizeof(char) * (_str_length(alias_name) + 1));
	if (!n_node->name)
	{
		free(n_node);
		return (NULL);
	}
	n_node->value = alias_value;
	_str_cpy(n_node->name, alias_name);
	if (*first_node)
	{
		tail = *first_node;
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = n_node;
	}
	else
		*first_node = n_node;
	return (n_node);
}

/**
 * append_node - add a node to the end of linked list passed as arg
 * @first_node: ptr to the first node
 * @dir: path directory
 * Return: ptr to new node or NULL if failed
 */
list_t *append_node(list_t **first_node, char *dir)
{
	list_t *tail;
	list_t *n_node = malloc(sizeof(list_t));

	if (!n_node)
		return (NULL);
	n_node->dir = dir;
	n_node->next = NULL;
	if (*first_node)
	{
		tail = *first_node;
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = n_node;
	}
	else
		*first_node = n_node;
	return (n_node);
}

/**
 * list_alias_free - frees link lists alias
 * @first_node: first node in a link list
 */
void list_alias_free(alias_t *first_node)
{
	alias_t *next;

	while (first_node)
	{
		next = first_node->next;
		free(first_node->name);
		free(first_node->value);
		free(first_node);
		first_node = next;
	}
}

/**
 * free_list - delet a link list from memory
 * @head: first node
 */
void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
