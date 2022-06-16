#include "main.h"

/**
 * main - main entry point of the program
 * @ac: count of command line arguments
 * @av: vector of command line arguments
 *
 * Description: first version (version 0.1) of the simple shell
 * program (ALX SE project)
 * Return: Always 0 (Success)
 */
int main(int ac, char **av)
{
	char *word, *command, *line = NULL, **args = NULL, **env = environ;
	size_t size = 1, n = 0;
	ssize_t num_char;
	void (*func)(char **, char **);

	(void) av;
	if (ac != 1)
		return (1);
	while (1)
	{
		do {
			printf("#cisfun$ ");
			num_char = my_getline(&line, &n, STDIN_FILENO);
			if (num_char == -1)
			{
				free(line), exit(1);
			} line[num_char - 1] = '\0';
		} while (strcmp(line, "\0") == 0);
		args = malloc(sizeof(char *) * size);
		if (args == NULL)
		{
			perror("Not enough memory\n");
			free(line);
			exit(1);
		} word = strtok(line, " ");
		while (word != NULL)
		{
			args[size - 1] = strdup(word);
			args = realloc(args, sizeof(char *) * (++size));
			word = strtok(NULL, " ");
		}
		args[size - 1] = NULL, command = get_command(args[0]), word = args[0];
		args[0] = command, free(word), func = get_func(args[0]);
		if (func == NULL)
		{
			perror("Error");
		}
		else
			func(args, env);
		free_args(args), size = 1, args = NULL;

	}
	return (0);
}