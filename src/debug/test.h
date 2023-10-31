/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:09:26 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/31 17:38:17 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
#define TEST_H
#include "../../include/minishell.h"
#define OK 0
#define ERR -1
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
int get_nstate(t_stack *stack, t_ptable **p_table);
int push_reduce(t_stack **stack, int reduce);
int add_tree(t_node **tree, t_stack **stack, int reduce);
void clear_stack(t_stack *stack);
int accept(void);
int reject(void);
t_node *fix_types(t_node *tree);
t_node *parser(t_token *input, t_ptable **table);
void clean_parser(t_node **tree, t_stack *stack, t_token *input, int r);
int	ft_get_next_line(int fd, char **line, int to_free);
t_ptable **init_table(void);
int	ms_build_tree(t_node **tree, t_node *reduc_node, t_stack **popped);
#endif