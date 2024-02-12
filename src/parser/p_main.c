/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:16:19 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/12 14:48:14 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


t_ptable	*get_entry(t_token *input, t_ptable **table, t_stack *stack)
{
	int			i;
	int			type;
	t_ptable	*entry;

	if (!stack)
		return (NULL);
	entry = NULL;
	type = -1;
	if (input)
		type = input->type;
	i = -1;
	while (table[++i])
	{
		if (table[i]->state == stack->state)
		{
			if (table[i]->token == type)
				return (table[i]);
			else if (table[i]->token == DEFAULT)
				entry = table[i];
		}
	}
	return (entry);
}

t_node	*parser(t_token *input, t_ptable **table)
{
	int			r;
	t_node		*tree;
	t_stack		*stack;
	t_token		*start;

	tree = NULL;
	start = input;
	stack = init_stack();
	r = process_input(&input, table, &stack, &tree);
	clean_parser(&tree, stack, start, r);
	return (fix_types(tree));
}
