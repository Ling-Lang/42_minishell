/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:14:50 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/05 12:06:04 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	ft_cd(char **arg)
{
	char	*home;

	home = getenv("HOME");
	if (!arg[1])
	{
		chdir(home);
		return (0);
	}
	if (ft_strlen(arg[1]) == 0)
		return (0);
	if (opendir(arg[1]) != NULL)
	{
		chdir(arg[1]);
		return (0);
	}
	ft_putstr_fd("minishell: cd: ", 2);
	perror(arg[1]);
	return (1);
}
