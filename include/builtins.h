/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:25:44 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/16 12:38:43 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
#include "minishell.h"
#include "structs.h"

int execute_builtin(char **arg, t_env **env);
int ft_echo(char **arg, int argc);
void clear();
int ft_cd(char **arg);
int ft_pwd(void);
int ft_export(t_env **env, char **arg);
// void ft_export_print(t_env *env, char **arg);
void ft_env(t_env **env);
int ft_exit(char **args, int argc);
int ft_unset(t_env **env, char **arg);
int remove_env(t_env **env, char *arg);
void free_env(t_env *env);
#endif