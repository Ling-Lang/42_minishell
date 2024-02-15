/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_push.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:26:42 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/15 11:32:11 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_stack	*create_new_input_node(t_token *input)
{
	t_stack	*new_node;

	new_node = (t_stack *)malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->type = input->type;
	new_node->state = -1;
	new_node->data = input->value;
	input->value = NULL;
	return (new_node);
}

int	push_input(t_stack **stack, t_token *input)
{
	t_stack	*new_node;

	new_node = create_new_input_node(input);
	if (!new_node)
		return (ERR);
	new_node->next = *stack;
	*stack = new_node;
	return (OK);
}

t_stack	*create_new_state_node(int state)
{
	t_stack	*new_node;

	new_node = (t_stack *)malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->type = -1;
	new_node->state = state;
	new_node->data = NULL;
	return (new_node);
}

int	push_state(t_stack **stack, int state)
{
	t_stack	*new_node;

	if (state == ERR)
		return (ERR);
	new_node = create_new_state_node(state);
	if (!new_node)
		return (ERR);
	new_node->next = *stack;
	*stack = new_node;
	return (OK);
}
