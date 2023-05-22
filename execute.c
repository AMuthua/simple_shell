#include "shell.h"

/**
 * execute - execute a command with entire path variables
 * @data: a pointer to the programs data
 * Return: iff success, return 0 otherwise return -1.
 */
int execute(data_of_program *data)
{
	int x = 0, status;
	pid_t pidd;

	/*check for built ins*/
	x = builtins_list(data);
	if (x != -1)/*if program was found*/
		return (x);

	/*check file system for program*/
	x = find_program(data);
	if (x)
	{/*program not found*/
		return (x);
	}
	else
	{/*if program was found*/
		pidd = fork();
		if (pidd == -1)
		{/*if fork call failed*/
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{/*child process, executes the program*/
			x = execve(data->tokens[0], data->tokens, data->env);
			if (x == -1)
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
