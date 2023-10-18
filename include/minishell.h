/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:15:40 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/18 13:15:52 by jkulka           ###   ########.fr       */
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

#	define RED "\e[0;31m"
#	define YEL "\e[0;33m"
#	define WHT "\e[0;37m"
#	define BLU "\e[0;34m"
/* Global Variable */
extern char *home_dir;
/* Commands */
// int list_files(char *path);
void ft_echo(char **arg);
void ft_cd(char **arg);
void clear();
void ft_wait_for_cmd(char **arg);
int execute_command(char **arg);
// int execute_with_output_redirection(const char *command, const char *output_file);
/* String Utils */
char *ft_last_word(char *str);
char *first_word(char *str);
char **ft_new_split(char *str);
#endif