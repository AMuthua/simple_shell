#include "shell.h"

/**
 * long_to_string - converts a number to a string
 * @number: number to be converted to a string
 * @string: buffer to save the number as a string
 * @base: base to convert number
 *
 * Return: Nothing
 */
void long_to_string(long number, char *string, int base)
{
	int index = 0, isNegative = 0;
	long x = number;
	char letters[] = {"0123456789abcdef"};

	if (x == 0)
		string[index++] = '0';

	if (string[0] == '-')
		isNegative = 1;

	while (x)
	{
		if (x < 0)
			string[index++] = letters[-(x % base)];
		else
			string[index++] = letters[x % base];
		x /= base;
	}
	if (isNegative)
		string[index++] = '-';

	string[index] = '\0';
	str_reverse(string);
}

/**
 * _atoi - converts string to integer
 *
 * @s: pointer to strng origin
 * Return: int of string or 0
 */
int _atoi(char *s)
{
	int k = 1;
	unsigned int num = 0;

	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			k *= -1;
		if (*s == '+')
			k *= +1;
		s++;
	}

	while ('0' <= *s && *s <= '9' && *s != '\0')
	{
		num = (num * 10) + (*s - '0');
		s++;
	}
	return (num * k);
}

/**
 * count_characters - count the number of characher in string
 *
 * @string: pointer to str origin
 * @character: string with chars to be counted
 * Return: int of string or 0
 */
int count_characters(char *string, char *character)
{
	int l = 0, count = 0;

	for (; string[l]; l++)
	{
		if (string[l] == character[0])
			count++;
	}
	return (count);
}
