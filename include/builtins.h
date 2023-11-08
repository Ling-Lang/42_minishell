/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:25:44 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/08 18:42:53 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
#include "minishell.h"
#include "structs.h"

int execute_builtin(char **arg, t_env *env);
void ft_echo(char **arg);
int ft_cd(char **arg);
void clear();
int ft_pwd(void);
void ft_export(t_env *env, char **arg);
void ft_export_print(t_env *env, char **arg);
void ft_env(t_env *env);
void ft_exit(char ***args);
#endif