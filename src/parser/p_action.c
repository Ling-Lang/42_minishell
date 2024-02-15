/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_action.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:44:06 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/15 12:08:40 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_popped(t_stack **popped, t_stack *stack)
{
	t_stack	*start;

	if (!(*popped))
		*popped = stack;
	else
	{
		start = *popped;
		while ((*popped)->next)
			*popped = (*popped)->next;
		(*popped)->next = stack;
		*popped = start;
	}
	stack->next = NULL;
}

t_stack	*pop_stack(t_stack **stack, int n)
{
	int		i;
	t_stack	*next;
	t_stack	*popped;

	popped = NULL;
	if (stack)
	{
		i = -1;
		while (++i < n)
		{
			next = (*stack)->next;
			free(*stack);
			*stack = next;
			next = (*stack)->next;
			add_popped(&popped, *stack);
			*stack = next;
		}
	}
	return (popped);
}
