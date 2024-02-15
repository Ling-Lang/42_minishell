/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_magic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:01:38 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/05 12:07:00 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	shift(t_stack **stack, t_token **input, int n_state)
{
	if (push_input(stack, *input) == ERR)
		return (ERR);
	if (push_state(stack, n_state) == ERR)
		return (ERR);
	*input = (*input)->next;
	return (OK);
}

int	reduce(t_stack **stack, t_ptable **ptable, t_ptable *entry, t_node **tree)
{
	int		n_state;
	t_stack	*popped;

	popped = pop_stack(stack, entry->reduce);
	if (!popped)
		return (-1);
	if (push_reduce(stack, entry->n_state))
		return (clear_stack(popped));
	n_state = get_nstate(*stack, ptable);
	if (push_state(stack, n_state))
		return (clear_stack(popped));
	if (add_tree(tree, &popped, entry->n_state))
		return (clear_stack(popped));
	clear_stack(popped);
	return (OK);
}
