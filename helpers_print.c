#include "shell.h"

/**
 * _print - writes an array of chars in the standbar output
 * @string: pointer to the array of chars
 * Return: the number of bytes written
 * On error, -1 is returned and errno is set appropiataley
 */
int _print(char *string)
{
	return (write(STDOUT_FILENO, string, str_length(string)));
}

/**
 * _printe - writes an array of chars in the standard error
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or On error,
 * -1 is returned and errno is set
 */
int _printe(char *string)
{
	return (write(STDERR_FILENO, string, str_length(string)));
}

/**
 * _print_error - writes an array of chars in the standard error
 * @data: a pointer to the programs data
 * @errorcode: error code to print
 * Return: the numbr of bytes written or On error,
 * -1 is returned or errno is set
 */
int _print_error(int errorcode, data_of_program *data)
{
	char string[10] = {'\0'};

	long_to_string((long) data->exec_counter, string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(data->tokens[0]);
		if (errorcode == 2)
			_printe(": Not acceptable: ");
		else
			_print(": can't cd to ");
		_printe(data->tokens[1]);
		_printe("/n");
	}
	else if (errorcode == 127)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(string);
		_printe(": ");
		_printe(data->command_name);
		_printe(": not found\n");
	}
	else if (errorcode == 126)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(string);
		_printe(": ");
		_printe(data->command_name);
		_printe(": Permission denied\n");
	}
	return (0);
}
