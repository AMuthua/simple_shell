#include "shell.h"

/**
 * expand_variables - expand variables
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_variables(data_of_program *data)
{
	int s, t;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	for (s = 0; line[s]; s++)
		if (line[s] == '#')
			line[s--] = '\0';
		else if (line[s] == '$' && line[s + 1] == '?')
		{
			line[s] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + 1 + 2);
		}
		else if (line[s] == '$' && (line[s + 1] == ' ' || line[s + 1] == '\0'))
			continue;
		else if (line[s] == '$')
		{
			for (t = 1; line[s + t] && line[s + t] != ' '; t++)
				expansion[t - 1] = line[s + t];
			temp = env_get_key(expansion, data);
			line[s] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + s + t);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * expand_alias - expands aliases
 * @data: a pointer to the struct of the programs data
 *
 * Return: nothing but sets errno
 */
void expand_alias(data_of_program *data)
{
	int s, t, expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (s = 0; line[s]; s++)
	{
		for (t = 0; line[s + t] && line[s + t] != ' '; t++)
			expansion[t] = line[s + t];
		expansion[t] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + s + t);
			line[s] = '\0';
			buffer_add(line, temp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			expanded = 1;
		}
		break;
	}
	if (expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * buffer_add - append string at the end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: nothing, but setts errno
 */

int buffer_add(char *buffer, char *str_to_add)
{
	int length, x;

	length = str_length(buffer);
	for (x = 0; str_to_add[x]; x++)
	{
		buffer[length + x] = str_to_add[x];
	}
	buffer[length + x] = '\0';
	return (length + x);
}
