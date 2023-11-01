/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:58:59 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/01 17:42:14 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "test.h"
const char *ttype_names[] = {
    "END",
    "WORD",
    "R_TO_FILE",
    "R_FROM_FILE",
    "GREATER",
    "LESS",
    "PIPE"
};

const char *e_action_names[] = {
    "NO_ACTION",
    "SHIFT",
    "REDUCE",
    "REJECT",
};
const char *e_rule_names[] = {
    "PIPE_SEQUENCE",
    "SIMPLE_COMMAND",
    "CMD_NAME",
    "CMD_WORD",
    "CMD_PREFIX",
    "CMD_SUFFIX",
    "IO_REDIRECT",
    "IOFILE",
    "FILENAME",
    "IO_HERE",
    "HERE_END"
};
void print_table(const t_ptable *table, int len)
{
    printf("State\tToken\tAction\tNext State\tReduce\n");
    for (int i = 0; i < len; i++)
    {
        printf("%d\t%d\t%d\t%d\t\t%d\n",
               table[i].state,
               table[i].token,
               table[i].action,
               table[i].n_state,
               table[i].reduce);
    }
}

void ft_print_tokens(t_token *token)
{
	t_token *cur;
	cur = token;
	while(cur)
	{
		ft_printf("Type: %s, Value: %s\n", ttype_names[cur->type - T_END - 1], (char *)cur->value);
		cur = cur->next;
	}
}
t_stack *init_stack(void)
{
	t_stack *init;
	
	init = (t_stack *)malloc(sizeof(*init));
	if(!init)
		return NULL;
	init->data = NULL;
	init->type = -1;
	init->state = 0;
	init->next = NULL;
	return (init);
}
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
int push_input(t_stack **stack, t_token *input)
{
    t_stack *new;

    new = (t_stack *)malloc(sizeof(*new));
    if(!new)
        return ERR;
    new->type = input->type;
    new->state = -1;
    new->data = input->value;
    input->value = NULL;
    new->next = *stack;
    *stack = new;
    return (OK);
}
int push_state(t_stack **stack, int state)
{
    t_stack *new;

    if(state == ERR)
        return ERR;
    new = (t_stack *)malloc(sizeof(*new));
    new->type = -1;
    new->state = state;
    new->data = NULL;
    new->next = *stack;
    *stack = new;
    return OK;
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
int	main(void)
{
    t_token *input;
    t_ptable **table = init_table();
    t_node *tree;
    char *str = readline(">> ");
    input = init_tokens(str);
    ft_print_tokens(input);
    tree = parser(input, table);
    char **tmp = iterate_tree(tree, init_args());
    // ft_printf("%s\n", tmp[0]);
    // execvp(tmp[0], tmp);
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
    // ft_print_tokens(input);
    while(r == OK)
    {
        entry = get_entry(input, table, stack);
        if(entry)
            ft_printf("Current state %d\nCurrent Token %d\n", entry->state, entry->token);
        if(entry && entry->action == SHIFT)
        {
            ft_printf("Shift to state %d\n", entry->n_state);
            r = shift(&stack, &input, entry->n_state);
        }
        else if(entry && entry->action == REDUCE)
        {
            ft_printf("Reducing using rule %d \n", entry->n_state);
            r = reduce(&stack, table, entry, &tree);
        }
        else if(entry && entry->action == ACCEPT)
        {
            r = accept();
        }
        else
        {
            r = reject();
        }
    }
    clean_parser(&tree, stack, start, r);
    return(fix_types(tree));
}
