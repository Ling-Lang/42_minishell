/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:07:09 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/05 12:06:06 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


bool	ft_check_n(char *str)
{
	int	i;

	if (!ft_strcmp(str, "-n"))
		return (true);
	if (str[0] == '-' && str[1] == 'n')
	{
		i = 1;
		while (str[++i])
		{
			if (str[i] != 'n')
				return (false);
		}
		return (true);
	}
	return (false);
}

int	ft_echo(char **arg, int argc)
{
	int		i;
	bool	has_flag;
	bool	start;

	start = true;
	has_flag = false;
	i = 0;
	while (arg[++i] && ft_check_n(arg[i]))
		has_flag = true;
	while (i < argc)
	{
		if (!start)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(arg[i], 1);
		if (start)
			start = false;
		++i;
	}
	if (argc >= 1 && !has_flag)
		ft_putchar_fd('\n', 1);
	return (0);
}
