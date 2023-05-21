#include "shell.h"

/**
 * print_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int print_alias(data_of_program *data, char *alias)
{
	int x, y, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_length(alias);
		for (x = 0; data->alias_list[x]; x++)
		{
			if (!alias || (str_compare(data->alias_list[x], alias, alias_length)
						&& data->alias_list[x][alias_length] == '='))
			{
				for (y = 0; data->alias_list[x][y]; y++)
				{
					buffer[y] = data->alias_list[x][y];
					if (data->alias_list[x][y] == '=')
						break;
				}
				buffer[y + 1] = '\0';
				buffer_add(buffer, ",");
				buffer_add(buffer, data->alias_list[x] + y + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - add, remove or show aliases
 * @data: struct for the programs data
 * @name: name of the requested alias.
 * Return: zero if success, or other number is declared
 */
char *get_alias(data_of_program *data, char *name)
{
	int x, alias_length;

	/*validate the arguments*/
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (x = 0; data->alias_list[x]; x++)
	{/*iterates through the environ*/
		if (str_compare(name, data->alias_list[x], alias_length) &&
				data->alias_list[x][alias_length] == '=')
		{/*returns the value of the key NAME =*/
			return (data->alias_list[x] + alias_length + 1);
		}
	}
	/*return NULL if not found*/
	return (NULL);

}

/**
 * set_alias - add, or overide alias
 * @alias_string: alias to be set in the form (name = 'value')
 * @data: struct for the programs data
 * Return: zero if success, or if other number is declared
 */
int set_alias(char *alias_string, data_of_program *data)
{
	int x, y;
	char buffer[250] = {'0'}, *temp = NULL;

	/*validation of arguments*/
	if (alias_string == NULL || data->alias_list == NULL)
		return (1);
	/*Alias to find char*/
	for (x = 0; alias_string[x]; x++)
		if (alias_string[x] != '=')
			buffer[x] = alias_string[x];
		else
		{
			temp = get_alias(data, alias_string + x + 1);
			break;
		}

	/*check for varname*/
	for (y = 0; data->alias_list[y]; y++)
		if (str_compare(buffer, data->alias_list[y], x) &&
				data->alias_list[y][x] == '=')
		{/*if alias exixts..*/
			free(data->alias_list[y]);
			break;
		}

	/*adding the alias */
	if (temp)
	{/*if in existence*/
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[y] = str_duplicate(buffer);
	}
	else /*if not in existence*/
		data->alias_list[y] = str_duplicate(alias_string);
	return (0);
}
