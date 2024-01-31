/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:59:14 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/31 12:59:42 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int process_input(t_token **input, t_ptable **table, t_stack **stack, t_node **tree)
{
	int			r;
	t_ptable	*entry;

	r = OK;
	while (r == OK)
	{
		entry = get_entry(*input, table, *stack);
		if (entry && entry->action == SHIFT)
			r = shift(stack, input, entry->n_state);
		else if (entry && entry->action == REDUCE)
			r = reduce(stack, table, entry, tree);
		else if (entry && entry->action == ACCEPT)
			r = 1;
		else
			r = -1;
	}
	return r;
}