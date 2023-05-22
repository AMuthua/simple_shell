#include "shell.h"

/**
 * builtins_list - search for match and execute the associate builtin
 * @data: struct for the rpgrams data
 * Return: the return of a function if there is a match
 * otherwise returns -1
 */
int builtins_list(data_of_program *data)
{
	int iterate;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd,},
		{"alias", builtin_alias},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL},
	};

	for (iterate = 0; options[iterate].builtin != NULL; iterate++)
	{
		if (str_compare(options[iterate].builtin, data->command_name, 0))
		{
			return (options[iterate].function(data));
		}
	}
	return (-1);
}
