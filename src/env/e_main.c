/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:55:32 by jkulka            #+#    #+#             */
/*   Updated: 2024/03/08 13:39:44 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_env(t_env **env, t_env *new)
{
	t_env	*cur;

	if (!(*env))
	{
		(*env) = new;
		return ;
	}
	cur = (*env);
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new;
}

void	ft_free_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		free((void *)(*env)->name);
		free((*env)->value);
		free((*env));
		*env = tmp;
	}
}
