/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:09:26 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/01 17:36:44 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
#define TEST_H
#include "../../include/minishell.h"

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
char **iterate_tree(t_node *node, char **args);
char **init_args(void);
#endif