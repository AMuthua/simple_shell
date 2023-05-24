#include "shell.h"

/**
 * builtin_exit - eix of the program with the status
 * @data: struct for the programs data
 * Return: zero if success, or other number if declared in arguments
 */

int builtin_exit(data_of_program *data)
{
	int a;

	if (data->tokens[1] != NULL)
	{/*if exists arg for exit, check if its a number*/
		for (a = 0; data->tokens[1][a]; a++)
			if ((data->tokens[1][a] < '0' || data->tokens[1][a] > '9')
					&& data->tokens[1][a] != '+')
			{/*if not a number*/
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * builtin_cd - change the current directory
 * @data: struct for the programs data
 * Return: zero if success, or other number if declared in the arguments
 */
int builtin_cd(data_of_program *data)
{
	char *dir_home = env_get_key("HOME", data), *dir_old = NULL;
	char old[128] = {0};
	int err_code = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			dir_old = env_get_key("OLDPWD", data);
			if (dir_old)
				err_code = set_work_directory(data, dir_old);
			_print(env_get_key("PWD", data));
			_print("\n");

			return (err_code);
		}
		else
		{
			return (set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old, 128);

		return (set_work_directory(data, dir_home));
	}
	return (0);
}

/**
 * set_work_directory - set the work directory
 * @data: struct for the programs data
 * @new_dir: path to be set as work directory
 * Return: zero if sucess, or other nmber if declared
 */
int set_work_directory(data_of_program *data, char *new_dir)
{
	char old[128] = {0};
	int error_code = 0;

	getcwd(old, 128);

	if (!str_compare(old, new_dir, 0))
	{
		error_code = chdir(new_dir);
		if (error_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDPWD", old, data);
	return (0);
}

/**
 * builtin_help - shows where the shell runs
 * @data: struct for the prgorams data
 * Return: zero if success, other number if declared
 */
int builtin_help(data_of_program *data)
{
	int x, lng = 0;
	char *ptr[6] = {NULL};

	ptr[0] = HELP_MSG;

	/*validation*/
	if (data->tokens[1] == NULL)
	{
		_print(ptr[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	ptr[1] = HELP_EXIT_MSG;
	ptr[2] = HELP_ENV_MSG;
	ptr[3] = HELP_SETENV_MSG;
	ptr[4] = HELP_UNSETENV_MSG;
	ptr[5] = HELP_CD_MSG;

	for (x = 0; ptr[x]; x++)
	{/*print lngth of string*/
		lng = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], ptr[x], lng))
		{
			_print(ptr[x] + lng + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * builtin_alias - add, remove ir show aliases
 * @data: struct for the programs data
 * Return: zero if success, or other number if delcared
 */
int builtin_alias(data_of_program *data)
{
	int m = 0;

	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++m])
	{
		if (count_characters(data->tokens[m], "="))
			set_alias(data->tokens[m], data);
		else
			print_alias(data, data->tokens[m]);
	}

	return (0);
}
