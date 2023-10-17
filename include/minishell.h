/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:15:40 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/17 13:13:50 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "../Libft/src/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#	define RED "\e[0;31m"
#	define YEL "\e[0;33m"
#	define WHT "\e[0;37m"
#	define BLU "\e[0;34m"
/* Global Variable */
char *home_dir;
/* Commands */
int list_files();
void clear();
void ft_wait_for_cmd(char **arg);
int execute_command(char **arg);
/* String Utils */
char *ft_last_word(char *str);
char *first_word(char *str);
char **ft_new_split(char *str);
#endif