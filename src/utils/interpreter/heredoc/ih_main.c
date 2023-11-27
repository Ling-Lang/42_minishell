/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ih_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:05:13 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/27 15:49:31 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"


int	ft_create_heredoc(t_node *tree, int ret, int *fd, int *num)
{
	int		tmp_fd;
	char	*file;
	char	*content;

	if (ret != 0)
		return (ret);
	file = ft_tmp_file(++(*num));
	tmp_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (tmp_fd > 0)
	{
		if (tree->data)
		{
			if (*num == 0)
				content = ft_get_next_tmp(tree->data, 1);
			else
				content = ft_get_next_tmp(tree->data, 0);
			if (content && ft_write_here(tmp_fd, &content, ft_strlen(content)) >= 0
				&& !ft_open_fd(tmp_fd, file, fd, *num))
                return (0);
		}
	}	
	free(file);
	return (ERR);
}
char	*ft_finalize_heredoc(char **buffer, char *p_limit)
{
	int		l_limit;
	char	*res;

	l_limit = 0;
	if (p_limit == NULL)
		p_limit = ft_strchr(*buffer, 0);
	else
		l_limit = (ft_strchr(p_limit, '\n') - p_limit + 1);
	if (p_limit[0] == '\n')
		l_limit = (ft_strchr(p_limit + 1, '\n') - p_limit);
	if (*buffer)
	{
		res = ft_substr(*buffer, 0, ft_strlen(*buffer) - l_limit);
		if (res)
		{
			free(*buffer);
			*buffer = NULL;
			return (res);
		}
	}
	free(*buffer);
	*buffer = NULL;
	return (NULL);
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
int	*ft_heredoc(t_node *tree, int symbol, int *stop)
{
	int	*fd;
	int	num;

	num = -1;
	fd = (int *)malloc(sizeof(*fd) * (symbol + 1));
	if (fd)
	{
		fd[symbol] = dup(STDIN_FILENO);
		if (!ft_exec_heredoc(tree, 0, fd, &num))
			return (fd);
	}
	*stop = 1;
	return (fd);
}
