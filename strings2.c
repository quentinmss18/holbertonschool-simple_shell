#include "shell.h"
/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: difference between first non-matching characters
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * free_cmd - free an array of strings
 * @str: array
 * Return: void
 */
void free_cmd(char **str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i])
		free(str[i++]);
	free(str);
}

/**
 * _strncmp - compare n characters from 2 strings
 * @s1: s1
 * @s2: s2
 * @n: compare till n
 * Return: ascii difference between s1(n) s2(n)
 */
int _strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int i = 0;

	while (s1[i] && s2[i] && s1[i] == s2[i] &&
			i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}

/**
 * _strdup - duplicate string
 * @str: string
 * Return: allocated string
 */

char *_strdup(char *str)
{
	int i = 0;
	char *dest;

	if (str == 0)
		return (0);
	dest = malloc(sizeof(char) * _strlen(str) + 1);
	if (!dest)
		return (0);
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
