/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:14:34 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/16 17:25:03 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void ft_sig(int sig)
{
    exit(sig);
}
void ft_handle_signals(void)
{
    signal(SIGINT, ft_sig);
    signal(SIGQUIT, ft_sig);
}

void ft_ignore_signals(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

int ft_get_exit_code(int e_code)
{
    if (WIFSIGNALED(e_code))
        return(128 + WTERMSIG(e_code));
    return (WEXITSTATUS(e_code));
}