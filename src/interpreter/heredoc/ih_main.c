/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ih_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:05:13 by jkulka            #+#    #+#             */
/*   Updated: 2024/03/07 14:32:22 by jkulka           ###   ########.fr       */
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

char *get_content(t_node *tree, int *num)
{
    if (*num == 0)
        return ft_get_next_tmp(tree->data, 1);
    else
        return ft_get_next_tmp(tree->data, 0);
}

int write_and_open(char *content, int tmp_fd, char *file, int *fd, int *num)
{
    if (content && ft_write_here(tmp_fd, &content, ft_strlen(content)) >= 0 && !ft_open_fd(tmp_fd, file, fd, *num))
        return 0;
    return ERR;
}

int ft_create_heredoc(t_node *tree, int ret, int *fd, int *num)
{
	char *file;
	int tmp_fd;
    char *content;
	int res;
	if (ret != 0)
        return ret;
    file = ft_tmp_file(++(*num));
    tmp_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);

    if (tmp_fd > 0 && tree->data)
	{
        char *content = get_content(tree, num);
        res = write_and_open(content, tmp_fd, file, fd, num);
        if (res == 0)
            return 0;
    }

    free(file);
    return ERR;
}

int calculate_l_limit(char *p_limit, char *buffer)
{
    int l_limit = 0;
    if (p_limit == NULL)
        p_limit = ft_strchr(buffer, 0);
    else
        l_limit = (ft_strchr(p_limit, '\n') - p_limit + 1);
    if (p_limit[0] == '\n')
        l_limit = (ft_strchr(p_limit + 1, '\n') - p_limit);
    return l_limit;
}

char *create_res(char **buffer, int l_limit)
{
    char *res;
	
	res = ft_substr(*buffer, 0, ft_strlen(*buffer) - l_limit);
    if (res)
	{
        free(*buffer);
        *buffer = NULL;
        return res;
    }
    return NULL;
}

char *ft_finalize_heredoc(char **buffer, char *p_limit)
{
    int l_limit;
	
	l_limit = calculate_l_limit(p_limit, *buffer);
    if (*buffer) 
	{
        char *res = create_res(buffer, l_limit);
        if (res)
            return res;
    }
    free(*buffer);
    *buffer = NULL;
    return NULL;
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
