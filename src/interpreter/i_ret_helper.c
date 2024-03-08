/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_ret_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:30:49 by jkulka            #+#    #+#             */
/*   Updated: 2024/03/08 13:32:11 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ret_to(t_node *tree)
{
	int	fd;

	fd = open(tree->r->r->data, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == ERR)
		return (perror(tree->r->r->data), ERR);
	if (dup2(fd, STDOUT_FILENO) == ERR)
		return (perror("minishell"), ERR);
	return (0);
}

int	append_to(t_node *tree)
{
	int	fd;

	fd = open(tree->r->r->data, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd == ERR)
		return (perror(tree->r->r->data), ERR);
	if (dup2(fd, STDOUT_FILENO) == ERR)
		return (perror("minishell"), ERR);
	return (0);
}

int	ret_from(t_node *tree)
{
	int	fd;

	fd = open(tree->r->r->data, O_RDONLY);
	if (fd == ERR)
		return (perror(tree->r->r->data), ERR);
	if (dup2(fd, STDIN_FILENO) == ERR)
		return (perror("minishell"), ERR);
	return (0);
}
