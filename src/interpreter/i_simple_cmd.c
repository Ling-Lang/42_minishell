/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_simple_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:40:28 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/20 12:49:25 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_args(char **args, t_env **env, t_return *ret)
{
	if (args[0])
	{
		if (check_builtin(args[0]))
			execute_builtin(args, env, ret);
		else
			ret->r_code = execute_command(args, *env);
		if (!check_builtin(args[0]) && ret->r_code > 0 && ret->r_code < 128)
			ft_error(args[0], ret->r_code);
	}
	free_str_array(args);
}

void	handle_fd(int *fd, t_return *ret)
{
	if (fd[0] != -1)
		if (restore_fd(fd) == ERR)
			ret->r_code = ERR;
}

void	simple_command(t_node *tree, int *fd, t_env **env, t_return *ret)
{
	char	**args;

	ret->r_code = 0;
	args = iterate_tree(tree, init_args());
	if (args)
	{
		handle_args(args, env, ret);
	}
	else
	{
		ret->r_code = ERR;
	}
	handle_fd(fd, ret);
}
