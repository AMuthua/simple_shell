#include "shell.h"

/**
 * str_length - returns the length of a string
 * @string: pointer to string
 * Return: length of string
 */
int str_length(char *string)
{
	int lng = 0;

	if (string == NULL)
		return (0);

	while (string[lng++] != '\0')
	{
	}
	return (--lng);
}

/**
 * str_duplicate - duplicates a string
 * @string: string to be compied
 * Return: pointer to the array
 */
char *str_duplicate(char *string)
{
	char *ans;
	int lng, m;

	if (string == NULL)
		return (NULL);

	lng = str_length(string) + 1;

	ans = malloc(sizeof(char) * lng);

	if (ans == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (m = 0; m < lng; m++)
	{
		ans[m] = string[m];
	}

	return (ans);
}

/**
 * str_compare - compare two string
 * @string1: string one, the shorter one
 * @string2: string two, the longer one
 * @number: number of chars to be compared, 0 if infinite
 * Return: 1 if the strings are equal, 0 if not equal
 */
int str_compare(char *string1, char *string2, int number)
{
	int iterate;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0)/* infinite */
	{
		if (str_length(string1) != str_length(string2))
			return (0);
		for (iterate = 0; string1[iterate]; iterate++)
		{
			if (string1[iterate] != string2[iterate])
				return (0);
		}
		return (1);
	}
	else/* the number of chars to be compared, if any*/
	{
		for (iterate = 0; iterate < number; iterate++)
		{
			if (string1[iterate] != string2[iterate])
				return (0);
		}
		return (1);
	}
}

/**
 * str_concat - concatenated two strings
 * @string1: streing to be concat
 * @string2: strng to be concat
 *
 * Return: pointer to the array
 */
char *str_concat(char *string1, char *string2)
{
	char *result;
	int lng1 = 0, lng2 = 0;

	if (string1 == NULL)
		string1 = "";
	lng1 = str_length(string1);

	if (string2 == NULL)
		string2 = "";
	lng2 = str_length(string2);

	result = malloc(sizeof(char) * (lng1 + lng2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/*cpy of string1*/
	for (lng1 = 0; string1[lng1] != '\0'; lng1++)
		result[lng1] = string1[lng1];
	free(string1);

	/*copu of string2*/
	for (lng2 = 0; string2[lng2] != '\0'; lng2++)
	{
		result[lng2] = string2[lng2];
		lng1++;
	}

	result[lng1] = '\0';
	return (result);
}

/**
 * str_reverse - reverses a string
 *
 * @string: pointer to string
 * Return: void
 */
void str_reverse(char *string)
{
	int n = 0, length = str_length(string) - 1;
	char hld;

	while (n < length)
	{
		hld = string[n];
		string[n++] = string[length];
		string[length--] = hld;
	}
}
