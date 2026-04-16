#include "shell.h"

/**
 * _atoi - convert a string to int value
 * @s: string
 * Description: run through the string skipping every
 * characters untill digits are found, if sign are found
 * determine the right sign by switching even with value 1
 * if no digits are found return 0
 * when digits are found convert them to int value
 * convert using base 10 parsing
 * Return: new converted value
 */
int _atoi(char *s)
{
	int i = 0;
	int sn = 1;
	unsigned int m = 0;

	while (s[i] >= 9 && s[i] <= 13)
		i++;
	while ((s[i] >= 58 && s[i] <= 126) || (s[i] >= 32 && s[i] <= 47))
	{
		if (s[i] == '-' || s[i] == '+')
			if (s[i] == '-')
				sn = -sn;
		i++;
	}
	if (!(s[i] >= '0' && s[i] <= '9'))
		return (0);
	while (s[i] >= '0' && s[i] <= '9')
	{
		m = m * 10 + s[i] - '0';
		i++;
	}
	return (m * sn);
}
