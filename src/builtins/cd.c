/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:14:50 by jkulka            #+#    #+#             */
/*   Updated: 2024/03/08 13:41:49 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_chdir(char *path, t_env **env)
{
	char	cwd[PATH_MAX];
	char	*arg;

	getcwd(cwd, sizeof(cwd));
	arg = ft_strjoin("OLDPWD=", cwd);
	ft_modify(arg, env);
	chdir(path);
}

int	ft_cd(char **arg, t_env **env)
{
	char	*home;

	home = getenv("HOME");
	if (!arg[1])
	{
		ft_chdir(home, env);
		return (0);
	}
	if (ft_strlen(arg[1]) == 0)
		return (0);
	if (opendir(arg[1]) != NULL)
	{
		ft_chdir(arg[1], env);
		return (0);
	}
	ft_putstr_fd("minishell: cd: ", 2);
	perror(arg[1]);
	return (1);
}
