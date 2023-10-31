/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:10:14 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/31 18:31:51 by jkulka           ###   ########.fr       */
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
        while ((*popped)->next)
            *popped = (*popped)->next;
        (*popped)->next = stack;
        *popped = start;
    }
    stack->next = NULL;
}
t_stack *pop_stack(t_stack **stack, int n)
{
    int i;
    t_stack *next;
    t_stack *popped;
    
    popped = NULL;
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

int get_nstate(t_stack *stack, t_ptable **p_table)
{
    int i;
    int state;
    int n_state;

    state = stack->next->state;
    i = -1;
    while(p_table[++i])
    {
        if(p_table[i]->state == state)
        {
            if(p_table[i]->token == stack->type)
                return (p_table[i]->n_state);
            else if(p_table[i]->token == DEFAULT)
                n_state = p_table[i]->n_state;
        }
    }
    return (n_state);
}

t_node *add_reduce_front(t_node **tree, int reduce)
{
    t_node *node;
    
    node = (t_node *)malloc(sizeof(*node));
    if(node)
    {
        node->type = -1;
        node->reduce = reduce;
        node->data = NULL;
        node->l = NULL;
        node->r = NULL;
        node->n = *tree;
        *tree = node;
        return (node);
    }
    return NULL;
}

void rm_node(t_node **tree, t_node *rem)
{
    t_node *prev;
    t_node *tmp;
    
    if(*tree == rem)
    {
        *tree = rem->n;
        return ;
    }
    else
    {  
        prev = NULL;
        tmp = *tree;
        while(tmp)
        {
            if(tmp == rem)
            {
                prev->n = tmp->n;
                return ;
            }
            prev = tmp;
            tmp = tmp->n;
        }
    }
}
t_node *find_reduce(t_node **tree, int reduce)
{
    t_node *start;
    t_node *res;

    res = NULL;
    start = *tree;
    *tree = (*tree)->n;
    while(*tree)
    {
        if((*tree)->reduce == reduce)
        {
            res = *tree;
            rm_node(&start, *tree);
            break ;
        }
        *tree = (*tree)->n;
    }
    *tree = start;
    return res;
}
t_node *convert_stack(t_stack *stack)
{
    t_node *node;

    node = (t_node *)malloc(sizeof(*node));
    if(node)
    {
        node->type = stack->type;
        node->reduce = -1;
        if(stack->type >= R_PIPE_SEQUENCE)
        {
            node->type = -1;
            node->reduce = stack->type;
        }
        node->data = stack->data;
        stack->data = NULL;
        node->l = NULL;
        node->r = NULL;
        node->n = NULL;
        return node;
    }
    return NULL;
}
int build_tree(t_node **tree, t_node *reduce_node, t_stack **stack)
{
    int i;
    t_node *child;
    t_stack *begin;

    i = -1;
    begin = *stack;
    while(*stack)
    {
        if((*stack)->type >= 500)
        {
            child = find_reduce(tree, (*stack)->type);
        }
        else
            child = convert_stack(*stack);
        if(++i == 0)
            reduce_node->r = child;
        else
            reduce_node->l = child;
        if(i == 1 && (*stack)->next)
            reduce_node = reduce_node->l;
        (*stack) = (*stack)->next;
    }
    *stack = begin;
    return 0;
}

int add_tree(t_node **tree, t_stack **stack, int reduce)
{
    t_node *reduce_node;
    
    reduce_node = add_reduce_front(tree, reduce);
    if(reduce_node)
    {
        if(!build_tree(tree, reduce_node, stack))
            return OK;
    }
    return ERR;
}

void clear_stack(t_stack *stack)
{
    t_stack *n;

    while(stack)
    {
        n = stack->next;
        free(stack->data);
        free(stack);
        stack = n;
    }
}

int accept(void)
{
    return 1;
}
int reject(void)
{
    return -1;
}
void loop_fix_types(t_node *node)
{
    if(!node)
        return ;
    if(node->reduce == R_FILENAME)
        node->r->type = A_FILE;
    if(node->reduce == R_HERE_END)
        node->r->type = A_LIMITER;
    if(node->reduce > R_CMD_WORD)
    {
        if(node->l && node->l->type == A_CMD)
            node->l->type = A_PARAM;
        if(node->r && node->r->type == A_CMD)
            node->r->type = A_PARAM;
    }
    loop_fix_types(node->l);
    loop_fix_types(node->r);
}
t_node *fix_types(t_node *tree)
{
    if(tree && tree->type == -1)
        tree->type = ROOT;
    loop_fix_types(tree);
    return tree;
}
void free_tree(t_node **node)
{
    if(*node)
    {
        free_tree(&(*node)->l);
        free_tree(&(*node)->r);
        if(!(*node)->l && !(*node)->r)
        {
            free((*node)->data);
            free(*node);
            *node = NULL;
        }
    }
}
void clear_token(t_token *token)
{
    t_token *n;
    while(token)
    {
        n = token->next;
        free(token->value);
        free(token);
        token = n;
    }
}
void clean_parser(t_node **tree, t_stack *stack, t_token *input, int r)
{
    if(r == -1)
        free_tree(tree);
    clear_stack(stack);
    clear_token(input);
}