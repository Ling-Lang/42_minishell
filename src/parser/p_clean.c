/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_clean.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:09:18 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/05 12:06:57 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tree(t_node **node)
{
	if (*node)
	{
		free_tree(&(*node)->l);
		free_tree(&(*node)->r);
		if (!(*node)->l && !(*node)->r)
		{
			free((*node)->data);
			free(*node);
			*node = NULL;
		}
	}
}

void	clean_parser(t_node **tree, t_stack *stack, t_token *input, int r)
{
	t_token	*tmp_token;

	if (r == ERR)
		free_tree(tree);
	clear_stack(stack);
	while (input)
	{
		tmp_token = input->next;
		free(input->value);
		free(input);
		input = tmp_token;
	}
}
