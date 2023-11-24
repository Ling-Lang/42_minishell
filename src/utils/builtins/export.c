/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:08:50 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/24 18:22:26 by ahocuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_env *set_env(char *envp)
{
    t_env *tmp;
    t_env *env;

    env = NULL;
    tmp = new_env(envp);
    if(!tmp)
        return NULL;
    add_env(&env, tmp);
    return env;
}

int ft_export(t_env **env, char **arg)
{
    int i;
    i = 1;
    t_env *tmp;
    if (!arg[1])
    {
        tmp = *env;
        while (tmp != NULL)
        {
            printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
            tmp = tmp->next;
        }
        return OK;
    }
    else
    {
        while(arg[i] != NULL)
        {
            if (strcmp(arg[i], "|") == 0)
                return OK;
            add_env(env, set_env(arg[i]));
            i++;
            if(arg[i] == NULL)
                return OK;
        }
    }
    return OK;
}
