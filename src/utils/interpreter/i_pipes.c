/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 03:58:22 by ahocuk            #+#    #+#             */
/*   Updated: 2023/12/05 00:17:29 by ahocuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	simple_command2(t_node *tree, int *fd, t_env **env)
{
	char	**args;
	char	***commands;
	int		num_commands;

	commands = NULL;
	num_commands = 0;
	args = iterate_tree2(tree, init_args());
	commands = add_pipe(args, &num_commands);
	execute_piped_commands(&commands, num_commands, env);
	pipe_free(commands, num_commands);
	if (fd[0] != -1)
		if (restore_fd(fd) == ERR)
			return (ERR);
	free_str_array(args);
	return (0);
}
// Process 41098: 9 leaks for 176 total leaked bytes.

void	handle_pipe(int prev_pipe_fd, int pipe_fd[2])
{
	if (prev_pipe_fd != -1)
	{
		dup2(prev_pipe_fd, STDIN_FILENO);
		close(prev_pipe_fd);
	}
	if (pipe_fd[1] != -1)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

void	child_process(char ****commands, int *params, int pipe_fd[2],
		t_env **env)
{
	int		i;
	int		prev_pipe_fd;
	pid_t	child_pid;

	i = params[0];
	prev_pipe_fd = params[1];
	child_pid = fork();
	if (child_pid == -1)
		exit(EXIT_FAILURE);
	if (child_pid == 0)
	{
		handle_pipe(prev_pipe_fd, pipe_fd);
		if (strcmp((*commands)[i][0], "export") == 0)
			ft_export_special(commands, i, env);
		else
			ft_execve((*commands)[i], *env);
		exit(EXIT_SUCCESS);
	}
	waitpid(child_pid, NULL, 0);
}

void	execute_piped_commands(char ****commands, int num_commands, t_env **env)
{
	int	prev_pipe_fd;
	int	pipe_fd[2];
	int	i;
	int	cp_call_params[2];

	prev_pipe_fd = -1;
	i = 0;
	while (i < num_commands)
	{
		if (i < num_commands - 1 && pipe(pipe_fd) == -1)
			exit(EXIT_FAILURE);
		cp_call_params[0] = i;
		cp_call_params[1] = prev_pipe_fd;
		child_process(commands, cp_call_params, pipe_fd, env);
		if (prev_pipe_fd != -1)
			close(prev_pipe_fd);
		if (i < num_commands - 1)
		{
			close(pipe_fd[1]);
			prev_pipe_fd = pipe_fd[0];
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
