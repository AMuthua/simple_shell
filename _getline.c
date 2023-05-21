#include "shell.h"

/**
 * _getline - read one line from the prompt.
 * @data: struct for the programs data
 *
 * Return: reading counting of bytes
 */

int _getline(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t bytes_read, a = 0;

	/* check if there not exists more commands in the array */
	/* and checks the logical operators */
	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
					(array_operators[0] == '|' && errno == 0))
	{
		/* fre the memory allocated in the array if it exists */
		for (a = 0; array_commands[a]; a++)
		{
			free(array_commands[a]);
			array_commands[a] = NULL;
		}

		/* read from the file descriptor int to buff */
		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		/* split lines for /n or ; */
		a = 0;
		do {
			array_commands[a] = str_duplicate(_strtok(a ? NULL : buff, "\n;"));
			/* checks and split for && and || operators*/
			a = check_logic_ops(array_commands, a, array_operators);
		} while (array_commands[a++]);
	}

	/*obtains the next command and remove it fot the array*/
	data->input_line = array_commands[0];
	for (a = 0; array_commands[a]; a++)
	{
		array_commands[a] = array_commands[a + 1];
		array_operators[a] = array_operators[a + 1];
	}

	return (str_length(data->input_line));
}


/**
 * check_logic_ops - checks and split for && and || operators
 * @array_commands: array of the commands.
 * @i: index in the array_commands to be checked
 * @array_operators: array of the logical operators for each previous command
 *
 * Return: index of the last command in the array_commands.
 */
int check_logic_ops(char *array_commands[], int i, char array_operators[])
{
	char *temp = NULL;
	int b;

	/*checks for the other & char in thecommand line*/
	for (b = 0; array_commands[i] != NULL && array_commands[i][b]; b++)
	{
		if (array_commands[i][b] == '&' && array_commands[i][b + 1] == '&')
		{
			/* split the line*/
			temp = array_commands[i];
			array_commands[i][b] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(temp + b + 2);
			i++;
			array_operators[i] = '&';
			free(temp);
			b = 0;
		}
		if (array_commands[i][b] == '|' && array_commands[i][b + 1] == '|')
		{
			/*split the line when chars || was found*/
			temp = array_commands[i];
			array_commands[i][b] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(temp + b + 2);
			i++;
			array_operators[i] = '|';
			free(temp);
			b = 0;
		}
	}
	return (i);
}
