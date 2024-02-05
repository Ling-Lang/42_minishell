/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 04:07:29 by ahocuk            #+#    #+#             */
/*   Updated: 2024/02/05 12:05:16 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_string_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	remove_pipe_symbol(char ***args)
{
	int	i;

	i = 0;
	while ((*args)[i] != NULL && ft_strchr((*args)[i], '|') == NULL)
		++i;
	if ((*args)[i] != NULL)
	{
		(*args)[i] = NULL;
		while ((*args)[++i] != NULL)
			(*args)[i] = NULL;
	}
}

void	shift_elements(char **array, int position)
{
	if (array == NULL || position < 0)
		return ;
	if (array[position + 1] == NULL)
	{
		array[position] = NULL;
		return ;
	}
	free(array[position]);
	while (array[position + 1] != NULL)
	{
		array[position] = array[position + 1];
		++position;
	}
	array[position] = NULL;
}

int	find_symbol(t_node *tree, int to_find, int n)
{
	if (!tree)
		return (n);
	if (tree->type == to_find)
		++n;
	n = find_symbol(tree->l, to_find, n);
	n = find_symbol(tree->r, to_find, n);
	return (n);
}
