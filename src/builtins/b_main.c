/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:02:29 by jkulka            #+#    #+#             */
/*   Updated: 2024/03/08 11:43:12 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_builtin(char **arg, t_env **env, t_return *ret)
{
	int	i;

	ret->r_code = 0;
	i = 0;
	while (arg[i])
		++i;
	if (!ft_strcmp(arg[0], "cd"))
		ret->r_code = ft_cd(arg, env);
	if (!ft_strcmp(arg[0], "pwd"))
		ret->r_code = ft_pwd();
	if (!ft_strcmp(arg[0], "exit"))
		ft_exit(arg, i, ret);
	if (!ft_strcmp(arg[0], "echo"))
		ret->r_code = ft_echo(arg, i);
	if (!ft_strcmp(arg[0], "export"))
		ft_export(env, arg);
	if (!ft_strcmp(arg[0], "env"))
		ft_env(env);
	if (!ft_strcmp(arg[0], "unset"))
		ft_unset(env, arg);
}
