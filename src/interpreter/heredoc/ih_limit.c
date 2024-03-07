/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ih_limit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:00:13 by jkulka            #+#    #+#             */
/*   Updated: 2024/03/07 14:29:03 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_free_limit(char **l_start, char **l_middle)
{
	free(*l_start);
	free(*l_middle);
}

char *create_res_limit(char *res, char *limit, int len, int pos)
{
    if (pos == 1)
	{
        ft_strcpy(res, limit);
        res[len - 1] = '\n';
    }
	else if (pos == 2) 
	{
        res[0] = '\n';
        ft_strcpy(res + 1, limit);
        res[len - 1] = '\n';
    }
    res[len] = '\0';
    return res;
}

char *ft_to_search(char *limit, int pos)
{
	int len;
    char *res;
	
    len = ft_strlen(limit) + pos;
	res = (char *)malloc(sizeof(*res) * (len + 1));
    if (res)
        return create_res_limit(res, limit, len, pos);
    return NULL;
}

char	*ft_find_limit(char *buffer, char *limit)
{
	char	*l_start;
	char	*l_middle;
	char	*p_limit;

	l_start = ft_to_search(limit, 1);
	l_middle = ft_to_search(limit, 2);
	p_limit = ft_strnstr(buffer, l_start, ft_strlen(buffer));
	if (p_limit != buffer)
	{
		p_limit = ft_strnstr(buffer, l_middle, ft_strlen(buffer));
		ft_free_limit(&l_start, &l_middle);
		if (p_limit)
			return (p_limit);
		else
			return (NULL);
	}
	ft_free_limit(&l_start, &l_middle);
	return (p_limit);
}

void	ft_redo_buffer(char **save)
{
	free(*save);
	*save = NULL;
}
