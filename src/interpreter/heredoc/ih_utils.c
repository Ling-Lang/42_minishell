/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ih_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:07:48 by jkulka            #+#    #+#             */
/*   Updated: 2024/03/08 13:21:18 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	calculate_l_limit(char *p_limit, char *buffer)
{
	int	l_limit;

	l_limit = 0;
	if (p_limit == NULL)
		p_limit = ft_strchr(buffer, 0);
	else
		l_limit = (ft_strchr(p_limit, '\n') - p_limit + 1);
	if (p_limit[0] == '\n')
		l_limit = (ft_strchr(p_limit + 1, '\n') - p_limit);
	return (l_limit);
}

char	*create_res(char **buffer, int l_limit)
{
	char	*res;

	res = ft_substr(*buffer, 0, ft_strlen(*buffer) - l_limit);
	if (res)
	{
		free(*buffer);
		*buffer = NULL;
		return (res);
	}
	return (NULL);
}

char	*get_content(t_node *tree, int *num)
{
	if (*num == 0)
		return (ft_get_next_tmp(tree->data, 1));
	else
		return (ft_get_next_tmp(tree->data, 0));
}

int	ft_exec_heredoc(t_node *tree, int ret, int *fd, int *num)
{
	if (!tree || ret == ERR)
		return (ret);
	if (tree->type == A_LIMITER)
		ret = ft_create_heredoc(tree, ret, fd, num);
	ret = ft_exec_heredoc(tree->l, ret, fd, num);
	ret = ft_exec_heredoc(tree->r, ret, fd, num);
	return (ret);
}

char	*ft_here_helper(char *limit, char *buffer, char *save, char *p_limit)
{
	buffer = readbuf(buffer);
	while (buffer)
	{
		p_limit = ft_check_buffer(&save, buffer, limit);
		if (p_limit || buffer[0] == '\0')
		{
			free(buffer);
			return (ft_finalize_heredoc(&save, p_limit));
		}
		buffer = readbuf(buffer);
	}
	if (!buffer)
		ft_redo_buffer(&save);
	return (buffer);
}
