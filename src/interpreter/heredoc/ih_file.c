/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ih_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:15:39 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/12 15:22:47 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_tmp_file(int num)
{
	char	*name;
	char	*tmp;

	name = ft_itoa(num);
	if (name)
	{
		tmp = name;
		name = ft_strjoin(name, (const char *)".tmp");
		free(tmp);
		if (name)
			return (name);
	}
	return (NULL);
}

char	*ft_init_buffer(void)
{
	char	*save;

	save = (char *)malloc(sizeof(*save));
	if (!save)
		return (NULL);
	save[0] = 0;
	return (save);
}

int	ft_manage_buffer(int t_free, char **save)
{
	if (t_free)
	{
		free(*save);
		*save = NULL;
	}
	if (!*save)
	{
		*save = ft_init_buffer();
		if (!*save)
			return (ERR);
	}
	return (0);
}

char	*ft_check_buffer(char **save, char *buffer, char *limit)
{
	char	*tmp;
	tmp = *save;
	*save = ft_strjoin(*save, buffer);
	free(tmp);
	return (ft_find_limit(*save, limit));
}

char	*ft_get_next_tmp(char *limit, int to_free)
{
    static char	*save;
    char		*p_limit;
    char		*buffer;

    if (ft_manage_buffer(to_free, &save) == ERR)
        return (NULL);
    p_limit = ft_find_limit(save, limit);
    if (!p_limit)
    {
        buffer = readline("> ");
		buffer = ft_strjoin(buffer, "\n");
        while (buffer)
        {
            p_limit = ft_check_buffer(&save, buffer, limit);
            if (p_limit || buffer[0] == '\0')
            {
                free(buffer);
                return (ft_finalize_heredoc(&save, p_limit));
            }
            free(buffer);
            buffer = readline("> ");
			buffer = ft_strjoin(buffer, "\n");
        }
        if (!buffer)
            ft_redo_buffer(&save);
    }
    else
        return (ft_finalize_heredoc(&save, p_limit));
    return (NULL);
}
