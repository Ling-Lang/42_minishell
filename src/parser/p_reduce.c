/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_reduce.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:54:50 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/20 14:15:23 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_stack	*create_new_reduce_node(int reduce)
{
	t_stack	*new_node;

	new_node = (t_stack *)malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->type = reduce;
	new_node->state = -1;
	new_node->data = NULL;
	return (new_node);
}

int	push_reduce(t_stack **stack, int reduce)
{
	t_stack	*new;

	new = create_new_reduce_node(reduce);
	if (!new)
		return (-1);
	new->next = *stack;
	*stack = new;
	return (0);
}
