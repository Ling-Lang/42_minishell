/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 03:58:22 by ahocuk            #+#    #+#             */
/*   Updated: 2023/11/27 04:31:17 by ahocuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	simple_command2(t_node *tree, int *fd, t_env **env)
{
	char	**args;
	char	**tmp;
	int		a;
	int		pipe;
	char	***commands;
	int		num_commands;
	int		i;

	a = 0;
	pipe = 1;
	commands = NULL;
	num_commands = 0;
	args = iterate_tree2(tree, init_args());
	while (args[a] != NULL)
	{
		if (strcmp(args[a], "|") == 0)
			pipe++;
		a++;
	}
	commands = (char ***)malloc(64 * sizeof(char **)); // 64 is max commands
	while (args[0] != NULL)
	{
		tmp = copy_string_array(args);
		remove_pipe_symbol(tmp);
		commands[num_commands++] = tmp;
		while (check_builtin(args[0]) != 5 && args[0] != NULL)
			shift_elements(args, 0);
		shift_elements(args, 0);
	}
	execute_piped_commands(&commands, num_commands, env);
	i = 0;
	while (i < num_commands)
	{
		free(commands[i]);
		++i;
	}
	free(commands);
	return (0);
}

void	execute_piped_commands(char ****commands, int num_commands, t_env **env)
{
	int		prev_pipe_fd;
	int		pipe_fd[2];
	int		i;
	pid_t	child_pid;

	prev_pipe_fd = -1;
	i = 0;
	while (i < num_commands)
	{
		if (i < num_commands - 1)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			if (prev_pipe_fd != -1)
			{
				dup2(prev_pipe_fd, STDIN_FILENO);
				close(prev_pipe_fd);
			}
			if (i < num_commands - 1)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			if (strcmp((*commands)[i][0], "export") == 0)
				ft_export_special(commands, i, env);
			else
			{
				execute_command2((*commands)[i]);
			}
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (prev_pipe_fd != -1)
			{
				close(prev_pipe_fd);
			}
			if (i < num_commands - 1)
			{
				close(pipe_fd[1]);
				prev_pipe_fd = pipe_fd[0];
			}
			waitpid(child_pid, NULL, 0);
		}
		++i;
	}
}
void	execute_command2(char **args)
{
	pid_t	child_pid;
	int		status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		execvp(args[0], args);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}
}
char	**copy_string_array(char **original)
{
	int		size;
	char	**copy;
	int		i;

	size = 0;
	while (original[size] != NULL)
		size++;
	copy = (char **)malloc((size + 1) * sizeof(char *));
	i = 0;
	while (i <= size)
	{
		if (original[i] != NULL)
		{
			copy[i] = strdup(original[i]);
			if (copy[i] == NULL)
			{
				free_string_array(copy);
				return (NULL);
			}
		}
		else
			copy[i] = NULL;
		i++;
	}
	return (copy);
}
