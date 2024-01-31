/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_action.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:44:06 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/31 12:59:38 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	push_input(t_stack **stack, t_token *input)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(*new));
	if (!new)
		return (ERR);
	new->type = input->type;
	new->state = -1;
	new->data = input->value;
	input->value = NULL;
	new->next = *stack;
	*stack = new;
	return (OK);
}

int	push_state(t_stack **stack, int state)
{
	t_stack	*new;

	if (state == ERR)
		return (ERR);
	new = (t_stack *)malloc(sizeof(*new));
	new->type = -1;
	new->state = state;
	new->data = NULL;
	new->next = *stack;
	*stack = new;
	return (OK);
}

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

int	push_reduce(t_stack **stack, int reduce)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(*new));
	if (!new)
		return (-1);
	new->type = reduce;
	new->state = -1;
	new->data = NULL;
	new->next = *stack;
	*stack = new;
	return (0);
}
