/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_redirects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:52:30 by jkulka            #+#    #+#             */
/*   Updated: 2024/03/08 13:32:21 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_handle_heredoc(int *h_fd)
{
	int	num;
	int	fd;

	num = 0;
	fd = h_fd[num];
	if (h_fd[num + 1] == -1)
		num = 0;
	else
		++num;
	if (dup2(fd, STDIN_FILENO) == ERR)
		return ((perror("minishell")), ERR);
	return (0);
}

int	handle_redirects_helper(t_node *tree, int r, int *h_fd)
{
	r = handle_redirects(tree->l, r, h_fd);
	r = handle_redirects(tree->r, r, h_fd);
	if (r == ERR)
		return (ERR);
	return (r);
}

int	handle_iofile(t_node *tree, int r)
{
	if (tree->l->type == A_R_TO_FILE)
		r = ret_to(tree);
	if (tree->l->type == A_RET_FROM_FILE)
		r = ret_from(tree);
	if (tree->l->type == A_GREATER)
		r = append_to(tree);
	return (r);
}

int	handle_redirects(t_node *tree, int r, int *h_fd)
{
	if (!tree || (tree && tree->type == A_PIPE))
		return (r);
	r = handle_redirects_helper(tree, r, h_fd);
	if (tree->reduce == R_IOFILE)
	{
		r = handle_iofile(tree, r);
	}
	if (tree->reduce == R_IO_HERE)
		r = ft_handle_heredoc(h_fd);
	return (r);
}
