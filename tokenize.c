#include "shell.h"
/**
 * tokenize - this function seperates the string using a delimiter
 * @data: a pointer to the programs data
 * Return: an array to different parts of a string
 */
void tokenize(data_of_program *data)
{
	char *delimit = " \t";
	int a, b, count = 2, length;

	length = str_length(data->input_line);
	if (length)
	{
		if (data->input_line[length - 1] == '\n')
			data->input_line[length - 1] = '\0';
	}

	for (a = 0; data->input_line[a]; a++)
	{
		for (b = 0; delimit[b]; b++)
		{
			if (data->input_line[a] == delimit[b])
				count++;
		}
	}
	data->tokens = malloc(count * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	a = 0;
	data->tokens[a] = str_duplicate(_strtok(data->input_line, delimit));
	data->command_name = str_duplicate(data->tokens[0]);
	while (data->tokens[a++])
	{
		data->tokens[a] = str_duplicate(_strtok(NULL, delimit));
	}
}
