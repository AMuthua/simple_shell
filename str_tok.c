#include "shell.h"
/**
 * _strtok - seperates strings with delimiters
 * @line: pointer to array we recieve in getline
 * @delim: charachters we mark off string in parts
 * Return: a pointer to the created token
 */
char *_strtok(char *line, char *delim)
{
	int a;
	static char *str;
	char *cpystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (a = 0; delim[a] != '\0'; a++)
		{
			if (*str == delim[a])
			break;
		}
		if (delim[a] == '\0')
			break;
	}
	cpystr = str;
	if (*cpystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (a = 0; delim[a] != '\0'; a++)
		{
			if (*str == delim[a])
			{
				*str = '\0';
				str++;
				return (cpystr);
			}
		}
	}
	return (cpystr);
}
