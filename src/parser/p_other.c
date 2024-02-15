/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_other.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:00:49 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/05 12:07:05 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_nstate(t_stack *stack, t_ptable **p_table)
{
	int	i;
	int	state;
	int	n_state;

	state = stack->next->state;
	i = -1;
	while (p_table[++i])
	{
		if (p_table[i]->state == state)
		{
			if (p_table[i]->token == stack->type)
				return (p_table[i]->n_state);
			else if (p_table[i]->token == DEFAULT)
				n_state = p_table[i]->n_state;
		}
	}
	return (n_state);
}

void	rm_node(t_node **tree, t_node *rem)
{
	t_node	*prev;
	t_node	*tmp;

	if (*tree == rem)
	{
		*tree = rem->n;
		return ;
	}
	else
	{
		prev = NULL;
		tmp = *tree;
		while (tmp)
		{
			if (tmp == rem)
			{
				prev->n = tmp->n;
				return ;
			}
			prev = tmp;
			tmp = tmp->n;
		}
	}
}

t_node	*find_reduce(t_node **tree, int reduce)
{
	t_node	*start;
	t_node	*res;

	res = NULL;
	start = *tree;
	*tree = (*tree)->n;
	while (*tree)
	{
		if ((*tree)->reduce == reduce)
		{
			res = *tree;
			rm_node(&start, *tree);
			break ;
		}
		*tree = (*tree)->n;
	}
	*tree = start;
	return (res);
}

int	build_tree(t_node **tree, t_node *reduce_node, t_stack **stack)
{
	int		i;
	t_node	*child;
	t_stack	*begin;

	i = -1;
	begin = *stack;
	while (*stack)
	{
		if ((*stack)->type >= 500)
		{
			child = find_reduce(tree, (*stack)->type);
		}
		else
			child = convert_stack(*stack);
		if (++i == 0)
			reduce_node->r = child;
		else
			reduce_node->l = child;
		if (i == 1 && (*stack)->next)
			reduce_node = reduce_node->l;
		(*stack) = (*stack)->next;
	}
	*stack = begin;
	return (0);
}

int	add_tree(t_node **tree, t_stack **stack, int reduce)
{
	t_node	*reduce_node;

	reduce_node = add_reduce_front(tree, reduce);
	if (reduce_node)
	{
		if (!build_tree(tree, reduce_node, stack))
			return (OK);
	}
	return (ERR);
}
