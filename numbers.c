#include "shell.h"

/**
 * _isdigit - checks if a char is a digit
 * @d: int/char to check
 * Return: 1 for digit else 0
 */
int _isdigit(int d)
{
	if (d >= '0' && d <= '9')
		return (1);
	return (0);
}

/**
 * _isnumber - checks if a string is digits only
 * @str: string
 * Return: 1 for numerical string else 0
 */
int _isnumber(char *str)
{
	int i = 0;

	if (!str)
		return (0);
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!_isdigit(str[i])) /* 1 chiffre obligatoire */
		return (0);
	while (str[i])
	{
		if (!_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
