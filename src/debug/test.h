/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:09:26 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/30 16:18:06 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
#define TEST_H

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
typedef struct s_ptable
{
    int state;
    int token;
    int action;
    int n_state;
    int reduce;
}   t_ptable;

typedef struct s_stack
{
    void *data;
    int type;
    int state;
    struct s_stack *next;
}   t_stack;

typedef struct s_node
{
    int type;
    int reduce;
    void *data;
    struct s_node *l;
    struct s_node *r;
    struct s_node *n;
}   t_node;
t_stack *pop_stack(t_stack **stack, int n);
int push_reduce(t_stack **stack, int reduce);
#endif