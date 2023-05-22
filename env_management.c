#include "shell.h"

/**
 * env_get_key - gets the value of an environment variable
 * @key: the environment variable of interest
 * @data: struct of the programs data
 * Return: a pointer to hte value of the variableor NULL if no exist
 */
char *env_get_key(char *key, data_of_program *data)
{
	int j, key_lng = 0;

	/*validate the arguments*/
	if (key == NULL || data->env == NULL)
		return (NULL);

	/*obtains length of variables*/
	key_lng = str_length(key);

	for (j = 0; data->env[j]; j++)
	{/*checks for the name*/
		if (str_compare(key, data->env[j], key_lng) && data->env[j][key_lng] == '=')
		{/*returns value of the key NAME*/
			return (data->env[j] + key_lng + 1);
		}
	}
	/*returns null if not found*/
	return (NULL);
}

/**
 * env_set_key - overwrite the value of the environment variable
 * or create if it does not exist
 * @key: name of the variable to be set
 * @value: new value
 * @data: structure of the programs data
 * Return: 1 if the parameters are NULL, 2 if there is an error 0 if success
 */

int env_set_key(char *key, char *value, data_of_program *data)
{
	int x, key_lng = 0, new_key = 1;

	/*validate the arguments*/
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/*obtaining the length of the variable*/
	key_lng = str_length(key);

	for (x = 0; data->env[x]; x++)
	{
		if (str_compare(key, data->env[x], key_lng) && data->env[x][key_lng] == '=')
		{/*if key already exists*/
			new_key = 0;
			/*free the variable*/
			free(data->env[x]);
			break;
		}
	}
	/*make a string key = value*/
	data->env[x] = str_concat(str_duplicate(key), "=");
	data->env[x] = str_concat(data->env[x], value);

	if (new_key)
	{
		data->env[x + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - remove a key from the environment
 * @key: the key to remove
 * @data: the structure of the programs data
 * Return: 1 of the key was removes, 0 if it does not exist
 */
int env_remove_key(char *key, data_of_program *data)
{
	int x, key_lng = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	/*obtaining length of the variable*/
	key_lng = str_length(key);

	for (x = 0; data->env[x]; x++)
	{
		if (str_compare(key, data->env[x], key_lng) && data->env[x][key_lng] == '=')
		{/*if key already exists remove them*/
			free(data->env[x]);
			/*moves the key a position down*/
			x++;
			for (; data->env[x]; x++)
			{
				data->env[x - 1] = data->env[x];
			}

			data->env[x - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ - prints the current environ
 * @data: struct for the programs data
 * Return: nothing
 */
void print_environ(data_of_program *data)
{
	int y;

	for (y = 0; data->env[y]; y++)
	{
		_print(data->env[y]);
		_print("\n");
	}
}
