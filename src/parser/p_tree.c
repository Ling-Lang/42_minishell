/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_tree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:10:14 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/05 12:07:16 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	loop_fix_types(t_node *node)
{
	if (!node)
		return ;
	if (node->reduce == R_FILENAME)
		node->r->type = A_FILE;
	if (node->reduce == R_HERE_END)
		node->r->type = A_LIMITER;
	if (node->reduce > R_CMD_WORD)
	{
		if (node->l && node->l->type == A_CMD)
			node->l->type = A_PARAM;
		if (node->r && node->r->type == A_CMD)
			node->r->type = A_PARAM;
	}
	loop_fix_types(node->l);
	loop_fix_types(node->r);
}

t_node	*fix_types(t_node *tree)
{
	if (tree && tree->type == -1)
		tree->type = ROOT;
	loop_fix_types(tree);
	return (tree);
}

t_node	*add_reduce_front(t_node **tree, int reduce)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(*node));
	if (node)
	{
		node->type = -1;
		node->reduce = reduce;
		node->data = NULL;
		node->l = NULL;
		node->r = NULL;
		node->n = *tree;
		*tree = node;
		return (node);
	}
	return (NULL);
}
