/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_exec_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:39:22 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/20 12:39:33 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_child(char **arg, t_env *env)
{
	int	ret;

	ret = ft_execve(arg, env);
	free_str_array(arg);
	exit(ret);
}

int	handle_parent(pid_t child)
{
	int		ec;
	pid_t	wait;

	wait = waitpid(child, &ec, 0);
	if (wait == ERR)
		return (ERR);
	return (ft_get_exit_code(ec));
}

int	execute_command(char **arg, t_env *env)
{
	pid_t	child;

	child = fork();
	if (child == ERR)
		return (ERR);
	if (child == 0)
		handle_child(arg, env);
	else
		return (handle_parent(child));
	return (ERR);
}
