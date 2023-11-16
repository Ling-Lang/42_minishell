/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 00:48:30 by ahocuk            #+#    #+#             */
/*   Updated: 2023/11/16 01:01:00 by ahocuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int ft_unset(t_env **env, char **arg)
{
    if (!arg[1])
        return ERR;
    int i = 1;
    while (arg[i]) 
    {
        if (remove_env(env, arg[i]) == ERR) 
            return ERR;
        i++;
    }

    return OK;
}

int remove_env(t_env **env, char *arg)
{
    if (!arg || !*env)
        return ERR;

    t_env *tmp = *env;
    t_env *prev = NULL;

    while (tmp) 
    {
        if (ft_strcmp(tmp->name, arg) == 0) 
        {
            if (prev) 
                prev->next = tmp->next;
            else 
                *env = tmp->next;
            free_env(tmp);
            return OK;
        }
        prev = tmp;
        tmp = tmp->next;
    }

    return ERR;
}

void free_env(t_env *env) 
{
    if (env) 
    {
        free(env->name);
        free(env->value);
        free(env);
    }
}