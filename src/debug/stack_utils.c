/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:10:14 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/30 16:17:59 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "test.h"

void add_popped(t_stack **popped, t_stack *stack)
{
    t_stack *start;
    
    if(!(*popped))
        *popped = stack;
    else
    {
        start = *popped;
        while((*popped)->next)
            *popped = (*popped)->next;
            *popped = start;
    }
    start->next = NULL;
}
t_stack *pop_stack(t_stack **stack, int n)
{
    int i = 0;
    t_stack *next;
    t_stack *popped;
    if(stack)
    {
        i = -1;
        while(++i < n)
        {
            next = (*stack)->next;
            free(*stack);
            *stack = next;
            next = (*stack)->next;
            add_popped(&popped, *stack);
            *stack = next;
        }
    }
    return popped;
}

int push_reduce(t_stack **stack, int reduce)
{
    t_stack *new;

    new = (t_stack *)malloc(sizeof(*new));
    if(!new)
        return -1;
    new->type = reduce;
    new->state = -1;
    new->data = NULL;
    new->next = *stack;
    *stack = new;
    return 0;
}
