/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:15:40 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/24 16:45:59 by jkulka           ###   ########.fr       */
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


/* Parser */
void ft_check_for_redirect(char **arg_org, t_env *env);
void ft_parse(char *str, t_env *env);
// void ft_check_for_input_redirect(char **arg);
/* Executor */
void ft_wait_for_cmd(char **arg, t_env *env);
int execute_command(char **arg);
void ft_cmd_new(t_token *token);
/* Lexer */
char **ft_new_split(char *str);
t_token	*init_tokens(char *str);
/* Utils */
t_env *ft_init(char **envp);
void ft_free(char ***arg);
void ft_redirect(char **arg, bool redirect, int fd, t_env *env);
#endif