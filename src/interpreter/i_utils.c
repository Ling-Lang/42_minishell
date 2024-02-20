/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:39:47 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/05 12:05:20 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**init_args(void)
{
	char	**res;

	res = (char **)malloc(sizeof(*res));
	if (!res)
		return (NULL);
	*res = NULL;
	return (res);
}

void	free_str_array(char **str)
{
	char	**start;

	if (str)
	{
		start = str;
		while (*str)
		{
			free(*str);
			++str;
		}
		free(start);
	}
}

void	*free_str_null(char **str)
{
	free_str_array(str);
	return (NULL);
}

int	arg_len(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		++i;
	return (i);
}

int	check_builtin(char *arg)
{
	if (ft_strcmp(arg, "cd") == 0 || ft_strcmp(arg, "export") == 0
		|| ft_strcmp(arg, "echo") == 0 || ft_strcmp(arg, "pwd") == 0
		|| ft_strcmp(arg, "exit") == 0 || ft_strcmp(arg, "unset") == 0
		|| ft_strcmp(arg, "env") == 0)
		return (1);
	if (ft_strcmp(arg, "|") == 0)
		return (5);
	return (0);
}
