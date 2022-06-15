#include "main.h"


/**
 * free_args - frees up the memory allocated to an array of strings
 * @args: dynamically allocated array of stringsy
 *
 * Return: void
 */
void free_args(char **args)
{
	size_t i;

	if (args == NULL)
		return;
	for (i = 0; args[i] != NULL; i++)
	{
		free(args[i]);
	}
	free(args);
}


/**
 * get_command - derives the command from a pathname
 * @str: pathname we wish to parse
 *
 * Return: pointer to the command string
 */
char *get_command(char *str)
{
	size_t size = 1;
	char *string, *command, *token, **args = NULL;

	if (str == NULL)
		return (NULL);
	string = strdup(str);
	args = malloc(sizeof(char *) * size);
	token = strtok(string, "/");
	while (token != NULL)
	{
		args[size - 1] = strdup(token);
		args = realloc(args, sizeof(char *) * (++size));
		token = strtok(NULL, "/");
	}
	args[size - 1] = NULL;
	command = strdup(args[size - 2]);
	free_args(args);
	free(string);
	return (command);
}

/**
 * my_getline - alternative to the standard getline function
 * @line: stores the line of text that we read
 * @len: length of the line of text read
 * @fd: file descriptor
 *
 * Return: number of characters read (success) or -1 (error)
 */
ssize_t my_getline(char **line, size_t *len, int fd)
{
	char buffer[30];
	size_t n, num = 0;

	fflush(stdout);
	if (line == NULL || len == NULL)
	{
		perror("Bad Arguments\n");
		return (-1);
	}
	if (*line == NULL)
	{
		*len = sizeof(buffer), *line = malloc(*len + 1);
		if (*line == NULL)
		{
			perror("Not enough memory\n");
			return (-1);
		}
	}
	(*line)[0] = '\0';
	while ((n = read(fd, &buffer, sizeof(buffer))) != 0)
	{
		if (*len - strlen(*line) < sizeof(buffer))
		{
			*len *= 2, *line = realloc(*line, *len + 1);
			if (*line == NULL)
			{
				perror("Unable to reallocate memory\n");
				free(*line);
				return (-1);
			}
		}
		strncat(*line, buffer, n);
		num += n;
		if ((*line)[num - 1] == '\n')
		{
			(*line)[num] = '\0';
			return ((ssize_t) strlen(*line));
		}
	}
	free(*line);
	return (-1);
}

