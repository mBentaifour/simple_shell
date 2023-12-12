#include "shell.h"

/**
 * _str_length - length of a string.
 * @str: Pointer to string.
 *
 * Return: length of string.
 */
int _str_length(const char *str)
{
	int len = 0;

	if (!str)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

/**
 * _str_cat - concantenate two strings.
 * @dest_str: Pointer to destination string.
 * @src_str: Pointer to source string.
 *
 * Return: Pointer to result string.
 */
char *_str_cat(char *dest_str, const char *src_str)
{
	const char *temp_src;
	char *temp_dest;

	temp_dest = dest_str;
	temp_src = src_str;
	while (*temp_dest != '\0')
		temp_dest++;
	while (*temp_src != '\0')
		*temp_dest++ = *temp_src++;

	*temp_dest = '\0';
	return (dest_str);
}

/**
 * _str_cmp - compares two strings.
 * @str1: first string.
 * @str2: second string.
 *
 * Return: 0 if str1 = str2,
 * positive if str1 > str2,
 * negative if str1 < str2.
 */
int _str_cmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if (*str1 != *str2)
		return (*str1 - *str2);
	return (0);
}

/**
 * _str_chr - search a character in a string.
 * @str: the searched string.
 * @character: character to look for.
 *
 * Return: pointer to the first occurence if character is found.
 * NULL - character is not found.
 */
char *_str_chr(char *str, char character)
{
	do {
		if (*str == character)
			return (str);
	} while (*str++ != '\0');
	return (NULL);
}
