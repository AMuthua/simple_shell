#include "shell.h"

int check_file(char *full_path);

/**
 * find_program - find a program in path
 * @data: a pointer to the program's data
 * Return: 0 if successful, errcode if not
 */
int find_program(data_of_program *data)
{
	int a = 0, code = 0;
	char **dirs;

	if (!data->command_name)
		return (2);

	/*if it's a full path or exec in same path*/
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	dirs = tokenize_path(data);/*search in path*/

	if (!dirs || !dirs[0])
	{
		errno = 127;
		return (127);
	}
	for (a = 0; dirs[a]; a++)
	{
		dirs[a] = str_concat(dirs[a], data->tokens[0]);
		code = check_file(dirs[a]);
		if (code == 0 || code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(dirs[a]);
			free_array_of_pointers(dirs);
			return (code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(dirs);
	return (code);
}

/**
 * tokenize_path - tokenize the path in directories
 * @data: a pointer to the programs data
 * Return: array of path directories
 */
char **tokenize_path(data_of_program *data)
{
	int b = 0;
	int counter_dir = 2;
	char **tokns = NULL;
	char *PATH;

	/*get path value*/
	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		/*path not found?*/
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	/*find number of dirs*/
	for (b = 0; PATH[b]; b++)
	{
		if (PATH[b] == ':')
			counter_dir++;
	}

	/*reserve space for arry og pointers*/
	tokns = malloc(sizeof(char *) * counter_dir);

	b = 0;
	tokns[b] = str_duplicate(_strtok(PATH, ":"));
	while (tokns[b++])
	{
		tokns[b] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokns);
}

/**
 * check_file - checks if a file exists, if its a directory and
 * if it has ecexution permissions
 * @full_path: pointer to the full fle name
 * Return: 0 on success, or error code if it exists.
 */
int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) || access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/*it file not exist*/
	errno = 127;
	return (127);
}
