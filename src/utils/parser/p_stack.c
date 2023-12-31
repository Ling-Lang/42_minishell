/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_stack.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:07:19 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/27 03:13:13 by ahocuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_node	*convert_stack(t_stack *stack)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(*node));
	if (node)
	{
		node->type = stack->type;
		node->reduce = -1;
		if (stack->type >= R_PIPE_SEQUENCE)
		{
			node->type = -1;
			node->reduce = stack->type;
		}
		node->data = stack->data;
		stack->data = NULL;
		node->l = NULL;
		node->r = NULL;
		node->n = NULL;
		return (node);
	}
	return (NULL);
}

void	clear_stack(t_stack *stack)
{
	t_stack	*n;

	while (stack)
	{
		n = stack->next;
		free(stack->data);
		free(stack);
		stack = n;
	}
}

t_stack	*init_stack(void)
{
	t_stack	*init;

	init = (t_stack *)malloc(sizeof(*init));
	if (!init)
		return (NULL);
	init->data = NULL;
	init->type = -1;
	init->state = 0;
	init->next = NULL;
	return (init);
}
