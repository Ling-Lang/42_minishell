/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:25:44 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/29 12:33:42 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"
# include "structs.h"

void	execute_builtin(char **arg, t_env **env, t_return (*ret));
int		ft_echo(char **arg, int argc);
void	clear(void);
int		ft_cd(char **arg);
int		ft_pwd(void);
int		ft_export(t_env **env, char **arg);
// void ft_export_print(t_env *env, char **arg);
void	ft_export_special(char ****commands, int index, t_env **env);
void	ft_env(t_env **env);
void	ft_exit(char **args, int argc, t_return (*ret));
int		ft_unset(t_env **env, char **arg);
int		remove_env(t_env **env, char *arg);
void	free_env(t_env *env);
int		contains_symbol(char **args, char symbol);
int		ft_dollar(char **args, char symbol);
int		ft_check_dollars(char **args);
void	ft_ex_print(t_env *tmp, t_env **env);
#endif