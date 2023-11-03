/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:16:19 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/03 13:00:42 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_ptable *get_entry(t_token *input, t_ptable **table, t_stack *stack)
{
    int i;
    int type;
    t_ptable *entry;
    
    if(!stack)
        return NULL;
    entry = NULL;
    type = -1;
    if(input)
        type = input->type;
    i = -1;
    while(table[++i])
    {
        if(table[i]->state == stack->state)
        {
            if(table[i]->token == type)
                return (table[i]);
            else if(table[i]->token == DEFAULT)
                entry = table[i];
        }
    }
    return (entry);
}

int shift(t_stack **stack, t_token **input, int n_state)
{
    if(push_input(stack, *input) == ERR)
        return ERR;
    if(push_state(stack, n_state) == ERR)
        return ERR;
    *input = (*input)->next;
    return OK;
}
int reduce(t_stack **stack, t_ptable **ptable, t_ptable *entry, t_node **tree)
{
    int n_state;
    t_stack *popped;
    
    popped = pop_stack(stack, entry->reduce);
    if(popped)
    {
        if(!push_reduce(stack, entry->n_state))
        {
            n_state = get_nstate(*stack, ptable);
            if(!push_state(stack, n_state))
            {
                if(!add_tree(tree, &popped, entry->n_state))
                {
                    clear_stack(popped);
                    return OK;
                }
            }
        }
        clear_stack(popped);
    }
    return -1;
}

t_node *parser(t_token *input, t_ptable **table)
{
    int r;
    t_node *tree;
    t_ptable *entry;
    t_stack *stack;
    t_token *start;

    r = OK;
    tree = NULL;
    start = input;
    stack = init_stack();
    while(r == OK)
    {
        entry = get_entry(input, table, stack);
        // if(entry)
            // ft_printf("Current state %d\nCurrent Token %d\n", entry->state, entry->token);
        if(entry && entry->action == SHIFT)
        {
            // ft_printf("Shift to state %d\n", entry->n_state);
            r = shift(&stack, &input, entry->n_state);
        }
        else if(entry && entry->action == REDUCE)
        {
            // ft_printf("Reducing using rule %d\n", entry->n_state);
            r = reduce(&stack, table, entry, &tree);
        }
        else if(entry && entry->action == ACCEPT)
            r = 1;
        else
        {
            r = -1;
        }
    }
    clean_parser(&tree, stack, start, r);
    return(fix_types(tree));
}
