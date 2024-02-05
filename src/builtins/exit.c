/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:13:05 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/05 12:06:11 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	ft_isnum(char *arg)
{
	int			sign;
	long int	res;
	int			ret;

	ret = 1;
	sign = 1;
	res = 0;
	if (ft_strlen(arg) >= 21)
		return (0);
	if (*arg == '-' || *arg == '+')
	{
		if (*arg == '-')
			sign = -1;
		++arg;
	}
	while (ft_isdigit(*arg))
	{
		res = (res * 10) + (*arg - 48);
		++arg;
	}
	if (sign == 1 && res < 0)
		ret = 0;
	else if (sign == -1 && (res * -1) > 0)
		ret = 0;
	return (ret);
}

static int	ft_check_exit_arg(char *arg)
{
	int	i;
	int	ret;

	ret = 0;
	if (!ft_isnum(arg))
		return (0);
	if (arg[0] == '-' || arg[0] == '+')
		i = 1;
	else
		i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]))
			ret = 1;
		else
			return (0);
		i++;
	}
	return (ret);
}

int	ft_sanitize_error(char **args, int argc)
{
	int	ret;

	ret = 0;
	if (argc == 1)
		return (0);
	if (argc >= 2)
	{
		if (!ft_check_exit_arg(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			ret = -1;
		}
	}
	if (argc > 2 && !ret)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (-2);
	}
	return (ret);
}

void	ft_exit(char **args, int argc, t_return *ret)
{
	if (argc == 1)
	{
		ret->r_code = 0;
		ret->should_exit = true;
	}
	else if (argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ret->r_code = 1;
		return ;
	}
	else if (ft_check_exit_arg(args[1]))
		ret->r_code = (unsigned int)ft_atoi(args[1]);
	else
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ret->r_code = 255;
	}
	ret->should_exit = true;
}
