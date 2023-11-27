/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:53:40 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/27 21:45:23 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_execve(char **args, t_env *env)
{
	int		ret;
	char	**envp;

	if (get_bin(&args[0], env) == ERR)
		return (ERR);
	envp = t_env_to_envp(env);
	if (!envp)
		return (ERR);
	ret = execve(args[0], args, envp);
	if (ret == ERR)
	{
		if (errno == EAGAIN)
			ret = 126;
		else
			ret = 127;
	}
	return (ret);
}

int	execute_command(char **arg, t_env *env)
{
	pid_t	child_pid;
	pid_t	wait_pid;
	int		ret;
	int		exit_code;

	child_pid = fork();
	if (child_pid == ERR)
		return (ERR);
	if (child_pid == 0)
	{
		ret = ft_execve(arg, env);
		free_str_array(arg);
		exit(ret);
	}
	else
	{
		wait_pid = waitpid(child_pid, &exit_code, 0);
		if (wait_pid == ERR)
			return (ERR);
	}
	return (ft_get_exit_code(exit_code));
}

int	simple_command(t_node *tree, int *fd, t_env **env)
{
	char	**args;
	int		r;

	r = 0;
	args = iterate_tree(tree, init_args());
	if (args)
	{
		if (args[0])
		{
			if (check_builtin(args[0]))
			{
				r = execute_builtin(args, env);
			}
			else
				r = execute_command(args, *env);
			if (!check_builtin(args[0]) && r > 0 && r < 128)
				ft_error(args[0], r);
		}
	}
	else
		r = ERR;
	if (fd[0] != -1)
		if (restore_fd(fd) == ERR)
			r = ERR;
	return (r);
}

int	ft_check_heredoc(t_node *tree, int *stop, int **fd)
{
	int	symbol;

	symbol = find_symbol(tree, A_LESS, 0);
	if (symbol)
	{
		ft_handle_signals();
		*fd = ft_heredoc(tree, symbol, stop);
		if (!fd)
			return (ERR);
		ft_restore_default();
		dup2((*fd)[symbol], STDIN_FILENO);
		close((*fd)[symbol]);
		(*fd)[symbol] = -1;
	}
	return (0);
}

int	exec_tree(t_node *tree, t_env **env)
{
	int	r;
	int	n;
	int	fd[2];
	int	*here_fd;
	int	stop;

	stop = 0;
	fd[0] = -1;
	r = 1;
	here_fd = NULL;
	if (ft_check_heredoc(tree, &stop, &here_fd) == ERR)
		return (ERR);
	if (!stop)
	{
		cache_fd((int *)fd);
		n = find_symbol(tree, A_PIPE, 0);
		if (handle_redirects(tree, 0, here_fd) != ERR)
		{
			if (n)
				r = simple_command2(tree, fd, env);
			else
				r = simple_command(tree, fd, env);
		}
	}
	return (r);
}
