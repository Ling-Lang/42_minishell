/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:58:59 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/30 16:18:47 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "test.h"

int			ft_get_next_line(int fd, char **line, int to_free);

t_ptable *init_table()
{
    int fd = open("test", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return NULL;
    }
    t_ptable *table = NULL;
    char *line = "test";
    int len = 0;

    // Count the number of lines in the file
    while (line)
    {
		line = get_next_line(fd);
        len++;
        free(line); // Free the memory allocated by ft_get_next_line
    }

    close(fd);
    fd = open("test", O_RDONLY);

    table = (t_ptable *)malloc(sizeof(t_ptable) * len);
    if (table == NULL)
    {
        perror("Error allocating memory");
        return NULL;
    }

    int j = 0;
	line = "test";
    while (line)
    {
		line = get_next_line(fd);
        char **split = ft_split(line, '\t');
        if (split && split[4])
        {
            table[j].state = ft_atoi(split[0]);
            table[j].token = ft_atoi(split[1]);
            table[j].action = ft_atoi(split[2]);
            table[j].n_state = ft_atoi(split[3]);
            table[j].reduce = ft_atoi(split[4]);
            j++;

            // Clean up the split array
            int k = 0;
            while (split[k])
            {
                free(split[k]);
                k++;
            }
            free(split);
        }

        free(line); // Free the memory allocated by ft_get_next_line
    }

    close(fd);
    // printf("%d\n", len);
    return table;
}
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
		ft_printf("Type: %s, Value: %s\n", ttype_names[cur->type - END - 1], (char *)cur->value);
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
        return -1;
    new->type = input->type;
    new->state = -1;
    new->data = input->value;
    input->value = NULL;
    new->next = *stack;
    *stack = new;
    return (0);
}
int push_state(t_stack **stack, int state)
{
    t_stack *new;

    if(state == -1)
        return -1;
    new = (t_stack *)malloc(sizeof(*new));
    new->type = -1;
    new->state = state;
    new->data = NULL;
    new->next = *stack;
    *stack = new;
    return 0;
}

int shift(t_stack **stack, t_token **input, int n_state)
{
    if(push_input(stack, *input) == -1)
        return -1;
    if(push_state(stack, n_state) == -1)
        return -1;
    *input = (*input)->next;
    return 0;
}
int reduce(t_stack **stack, t_ptable **ptable, t_ptable *entry, t_node **tree)
{
    int n_state;
    t_stack *popped;

    popped = pop_stack(stack, entry->n_state);
    if(popped)
    {
        if(!push_reduce(stack, entry->n_state))
        {
            // n_state = get_n_state(*)
        }
    }
}
int	main(void)
{
	char str[] = "ls -l > test.txt";
	t_token *tokens;
	t_token *cur;
    t_ptable *tmp;
	t_stack *stack = init_stack();
	tokens = init_tokens(str);
	ft_print_tokens(tokens);
	t_ptable *tbl = init_table();
	int i = 0;
    int r  = 0;
    while(r == 0)
    {
        tmp = get_entry(tokens, &tbl, stack);
        // ft_printf("%d\t%d\t%s\n", stack->state, stack->type, stack->data);
        ft_printf("%s\n", tokens->value);
        if(tmp && tmp->action == SHIFT)
            r = shift(&stack, &tokens, tmp->n_state);
        else if(tmp && tmp->action == REDUCE)
            ft_printf("Reduce \n");
        else
        {
            // tmp = get_entry(tokens, &tbl, stack);
            ft_printf("%d", tmp->action);
            break;
        }
        // ft_printf("%d\t%d\t%d\n", stack->state, stack->type, stack->data);
    }
}