/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_main_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:32:42 by jkulka            #+#    #+#             */
/*   Updated: 2024/03/08 13:33:21 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_split(char **split)
{
	int	j;

	j = -1;
	while (split[++j])
		free(split[j]);
	free(split);
}

char	**add_args(char **args, char **split)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		args = add_arg_back(args, split[i]);
		if (!args)
		{
			free_split(split);
			return (NULL);
		}
	}
	return (args);
}

char	**add_cmd(char **args, t_node *node)
{
	char	**split;

	split = ft_split(node->data, ' ');
	if (!split)
		return (NULL);
	args = add_args(args, split);
	if (!args)
		return (NULL);
	free_split(split);
	return (args);
}
