/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ih_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:05:13 by jkulka            #+#    #+#             */
/*   Updated: 2024/03/08 13:16:29 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

int	ft_create_heredoc(t_node *tree, int ret, int *fd, int *num)
{
	char	*file;
	int		tmp_fd;
	char	*content;

	if (ret != 0)
		return (ret);
	file = ft_tmp_file(++(*num));
	tmp_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (tmp_fd > 0 && tree->data)
	{
		content = get_content(tree, num);
		if (content && ft_write_here(tmp_fd, &content, ft_strlen(content)) >= 0
			&& !ft_open_fd(tmp_fd, file, fd, *num))
			return (0);
	}
	free(file);
	return (ERR);
}

char	*ft_finalize_heredoc(char **buffer, char *p_limit)
{
	int		l_limit;
	char	*res;

	l_limit = calculate_l_limit(p_limit, *buffer);
	if (*buffer)
	{
		res = create_res(buffer, l_limit);
		if (res)
			return (res);
	}
	free(*buffer);
	*buffer = NULL;
	return (NULL);
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
