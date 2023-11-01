/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:15:40 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/01 18:56:14 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "../Libft/src/libft.h"
#include "builtins.h"
#include "structs.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <signal.h>

#	define RED "\e[0;31m"
#	define YEL "\e[0;33m"
#	define WHT "\e[0;37m"
#	define BLU "\e[0;34m"
#   define OK 0
#   define ERR -1

/* Interpreter*/
char **iterate_tree(t_node *node, char **args);
void free_str_array(char **str);
int arg_len(char **arg);
char **init_args(void);

/* Parser */
t_node *parser(t_token *input, t_ptable **table);
int push_state(t_stack **stack, int state);
int push_input(t_stack **stack, t_token *input);
t_stack *pop_stack(t_stack **stack, int n);
int push_reduce(t_stack **stack, int reduce);
int get_nstate(t_stack *stack, t_ptable **p_table);
int add_tree(t_node **tree, t_stack **stack, int reduce);
t_node *add_reduce_front(t_node **tree, int reduce);
t_node *convert_stack(t_stack *stack);
t_stack *init_stack(void);
t_node *fix_types(t_node *tree);
void clear_stack(t_stack *stack);
void clean_parser(t_node **tree, t_stack *stack, t_token *input, int r);
// void ft_check_for_input_redirect(char **arg);
/* Executor */
void ft_wait_for_cmd(char **arg, t_env *env);
int execute_command(char **arg);
void ft_cmd_new(t_token *token);


/* Lexer */
char **ft_new_split(char *str);
t_token	*init_tokens(char *str);
int	get_token_len(char *str);
int	is_separator(char s);
int	leading_separators(char *str, int len);
t_token	*create_token(char *str, int len);
int	get_token_type(char *str);
void	add_token(t_token **tokens, t_token *new_token);
void init_quote_struct(t_quote *q);

/* Utils */
void ft_init(char **envp, t_env **env);
t_ptable **init_table(void);
void ft_free(char ***arg);
char *ft_strncpy(char *src, char *dst, int n);
void ft_redirect(char **arg, bool redirect, int fd, t_env *env);
int	ft_get_next_line(int fd, char **line, int to_free);
#endif