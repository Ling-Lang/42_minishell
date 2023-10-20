/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:15:40 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/20 12:59:36 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "../Libft/src/libft.h"
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
/* Global Variable */

/* Builtins */
void ft_echo(char **arg);
void ft_cd(char **arg);
void clear();
void ft_pwd(void);

/* Parser */
void ft_check_for_redirect(char **arg_org);
void ft_parse(char *str);

/* Executor */
void ft_wait_for_cmd(char **arg);
int execute_command(char **arg);
/* Lexer */
char **ft_new_split(char *str);

/* Utils */
void ft_free(char ***arg);
void ft_redirect(char **arg, bool redirect, int fd);
#endif