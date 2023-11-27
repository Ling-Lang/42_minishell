/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:57:00 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/27 03:15:40 by ahocuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*ft_init(char **envp)
{
	t_env	*tmp;
	t_env	*env;

	env = NULL;
	while (*envp)
	{
		tmp = new_env(*envp);
		if (!tmp)
			return (NULL);
		add_env(&env, tmp);
		envp++;
	}
	return (env);
}
