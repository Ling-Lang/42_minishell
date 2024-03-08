/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_exec_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:53:40 by jkulka            #+#    #+#             */
/*   Updated: 2024/03/08 13:33:37 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	initialize_exec_tree(int *stop, int *fd, int **here_fd, t_return *ret)
{
	*stop = 0;
	fd[0] = -1;
	ret->r_code = 1;
	*here_fd = NULL;
}

void	exec_tree(t_node *tree, t_env **env, t_return *ret)
{
	int	fd[2];
	int	*here_fd;
	int	stop;
	int	n;

	initialize_exec_tree(&stop, fd, &here_fd, ret);
	if (ft_check_heredoc(tree, &stop, &here_fd) == ERR)
		return ;
	if (!stop)
	{
		cache_fd((int *)fd);
		n = find_symbol(tree, A_PIPE, 0);
		if (handle_redirects(tree, 0, here_fd) != ERR)
		{
			if (n)
				ret->r_code = simple_command2(tree, fd, env);
			else
				simple_command(tree, fd, env, ret);
		}
	}
	clean_here(here_fd);
}
