/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:54:16 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/27 03:15:04 by ahocuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_error(char *arg, int r)
{
	if (r == 127)
	{
		write(2, "minishell: ", 11);
		write(2, arg, ft_strlen(arg));
		write(2, ": command not found\n", 20);
	}
}
