/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_execve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:37:54 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/20 12:38:18 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_error(int ret)
{
	if (ret == ERR)
	{
		if (errno == EAGAIN)
			return (126);
		else
			return (127);
	}
	return (ret);
}

int	ft_execve(char **args, t_env *env)
{
	int		ret;
	char	**envp;

	if (get_bin(&args[0], env) == ERR)
		return (ERR);
	envp = t_env_to_envp(env);
	if (!envp)
		return (ERR);
	ret = execve(args[0], args, envp);
	return (handle_error(ret));
}
