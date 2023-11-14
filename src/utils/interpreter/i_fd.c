/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_fd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:54:51 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/14 14:09:48 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	cache_fd(int *fd)
{
	fd[READ] = dup(STDIN_FILENO);
	fd[WRITE] = dup(STDOUT_FILENO);
}

int	restore_fd(int *fd)
{
	fd[READ] = dup2(fd[READ], STDIN_FILENO);
	fd[WRITE] = dup2(fd[WRITE], STDOUT_FILENO);
	if(fd[READ] == ERR || fd[WRITE] == ERR)
		return ERR;
	return (0);
}
