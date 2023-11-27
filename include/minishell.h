/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:15:40 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/27 16:06:12 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "../Libft/src/libft.h"
#include "builtins.h"
#include "structs.h"
#include "get_next_line.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

#	define RED "\e[0;31m"
#	define YEL "\e[0;33m"
#	define WHT "\e[0;37m"
#	define BLU "\e[0;34m"
#   define OK 0
#   define ERR -1
#   define TBL_PATH "./src/utils/parser/table"
/* Interpreter*/
char **iterate_tree(t_node *node, char **args);
char	**iterate_tree2(t_node *node, char **args);
void free_str_array(char **str);
int arg_len(char **arg);
char **init_args(void);
int execute_command(char **arg, t_env *env);
int exec_tree(t_node *tree, t_env **env);
int check_builtin(char *arg);
void	cache_fd(int *fd);
int	restore_fd(int *fd);
int	handle_redirects(t_node *tree, int r, int *h_fd);
int handle_redirects2(t_node *tree, int r, int *h_fd);
void shift_elements(char **array, int position);
void remove_pipe_symbol(char **args);
char** copy_string_array(char **original);
void parse_and_execute(char **command);
void execute_command2(char **args);
void free_string_array(char **array);
int	find_symbol(t_node *tree, int to_find, int n);
int	simple_command2(t_node *tree, int *fd, t_env **env);
void	execute_piped_commands(char ****commands, int num_commands, t_env **env);
/* Heredoc */
int *ft_heredoc(t_node *tree, int symbol, int *stop);
char *ft_tmp_file(int num);
char *ft_find_limit(char *buffer, char *limit);
void ft_redo_buffer(char **save);
char *ft_finalize_heredoc(char **buffer, char *p_limit);
int ft_open_fd(int fd, char *file, int *here_fd, int num);
int ft_write_here(int fd, char **str, int len);
char *ft_get_next_tmp(char *limit, int free);

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
void free_tree(t_node **node);
void free_table(t_ptable **table);

/* Lexer */
char **ft_new_split(char *str);
t_token	*init_tokens(char *str);
int	get_token_len(char *str);
int	is_separator(char s);
int	leading_separators(char *str, int len);
t_token	*create_token(char *str, int len);
int	get_token_type(char *str, int len);
void	add_token(t_token **tokens, t_token *new_token);
void init_quote_struct(t_quote *q);


/* Expander */
void    ft_sanitize_tokens(t_token **input, t_env *env, int l_ret);
int ft_str_len_quotes(char *str);
char *ft_rem_quotes(char *str, t_env *env, int l_ret);
char *ft_get_last_ret(int l_ret);

/* Utils */
t_env *ft_init(char **envp);
t_ptable **init_table(void);
void ft_free(char ***arg);
char *ft_strncpy(char *src, char *dst, int n);
void ft_redirect(char **arg, bool redirect, int fd, t_env *env);
int	ft_get_next_line(int fd, char **line, int to_free);
void *free_str_null(char **str);
void clear_token(t_token *token);
void ft_error(char *arg, int r);
void ft_handle_signals(void);
void	ft_restore_default(void);
int ft_get_exit_code(int e_code);

/* envs */
void	add_env(t_env **env, t_env *new);
t_env	*new_env(char *env);
char	**t_env_to_envp(t_env *env);
char *get_env(char *find, t_env *env);
int get_bin(char **arg, t_env *env);
void ft_free_env(t_env **env);
void pipe_free(char	***commands, int num_commands);
char***	add_pipe(char** args, int* num_commands);

#endif
