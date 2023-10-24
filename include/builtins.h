/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:25:44 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/24 16:50:35 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
#include "minishell.h"
#include "structs.h"

void ft_echo(char **arg);
void ft_cd(char **arg);
void clear();
void ft_pwd(void);
void ft_export(t_env *env, char **arg);
void ft_export_print(t_env *env, char **arg);
void ft_env(t_env *env);

void ft_new_cd(t_token *token);

#endif