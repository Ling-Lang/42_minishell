/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:14:34 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/27 21:26:03 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		close(0);
	}
}

void	ft_handle_signals(void)
{
	signal(SIGINT, ft_sig);
	signal(SIGQUIT, ft_sig);
}

void	ft_restore_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	ft_get_exit_code(int e_code)
{
	if (WIFSIGNALED(e_code))
		return (128 + WTERMSIG(e_code));
	return (WEXITSTATUS(e_code));
}
