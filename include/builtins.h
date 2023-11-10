/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:25:44 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/10 03:35:15 by ahocuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
#include "minishell.h"
#include "structs.h"

int execute_builtin(char **arg, t_env **env);
void ft_echo(char **arg);
int ft_cd(char **arg);
void clear();
int ft_pwd(void);
int ft_export(t_env **env, char **arg);
void ft_export_print(t_env *env, char **arg);
void ft_env(t_env **env);
void ft_exit(char ***args);
#endif