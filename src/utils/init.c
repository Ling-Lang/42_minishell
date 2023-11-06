/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:57:00 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/06 14:55:46 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


t_env *ft_init(char **envp)
{
    t_env *tmp;
    t_env *env;
    tmp = NULL;

    env = NULL;
    while(*envp)
    {
        tmp = new_env(*envp);
        if(!tmp)
            return NULL;
        add_env(&env, tmp);
        envp++;
    }
    return env;
}