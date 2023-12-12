#include "shell.h"

/**
 * _str_n_cat - concantenates two strings.
 * @dest_str: destination str.
 * @src_str: source str.
 * @num: number of bytes to copy from source.
 *
 * Return: result string if modified.
 */
char *_str_n_cat(char *dest_str, const char *src_str, size_t num)
{
	size_t dest_length = _str_length(dest_str);
	size_t index;

	for (index = 0; index < num && src_str[index] != '\0'; index++)
		dest_str[dest_length + index] = src_str[index];
	dest_str[dest_length + index] = '\0';

	return (dest_str);
}

/**
 * _str_cpy - copies string from source to destination
 * @dest_str: str destination
 * @src_str: str source
 *
 * Return: ptr to dest
 */
char *_str_cpy(char *dest_str, const char *src_str)
{
	size_t index;

	for (index = 0; src_str[index] != '\0'; index++)
		dest_str[index] = src_str[index];
	dest_str[index] = '\0';
	return (dest_str);
}

/**
 * _str_n_cmp - compares two strings.
 * @str1: first string.
 * @str2: second string.
 * @num: number of characters
 *
 * Return: 0 if str1 and str2 match.
 * positive if str1 > str2.
 * negaive if str1 < str2.
 */
int _str_n_cmp(const char *str1, const char *str2, size_t num)
{
	size_t index;

	for (index = 0; str1[index] && str2[index] && index < num; index++)
	{
		if (str1[index] > str2[index])
			return (str1[index] - str2[index]);
		else if (str1[index] < str2[index])
			return (str1[index] - str2[index]);
	}
	if (index == num)
		return (0);
	else
		return (-15);
}

/**
 * _str_spn - returns the length of a substitution.
 * @str: searched string.
 * @pref: start of substring
 *
 * Return: Num of bytes
 */
int _str_spn(char *str, char *pref)
{
	int i, num_bytes = 0;

	while (*str)
	{
		for (i = 0; pref[i]; i++)
		{
			if (*str == pref[i])
			{
				num_bytes++;
				break;
			}
		}
		str++;
	}
	return (num_bytes);
}
