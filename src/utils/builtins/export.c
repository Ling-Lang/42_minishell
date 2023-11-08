/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:08:50 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/08 18:45:29 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void ft_export(t_env *env, char **arg)
{
    int i = 0;
    t_env *tmp;
    tmp = env;
    if(arg[1] == NULL)
    {
        while(tmp->next != NULL)
        {
            printf("%s=%s\n", tmp->name, tmp->value);
            tmp = tmp->next;
        }
    }
    else
        ft_export_print(env, arg);
}

void ft_export_print(t_env *env, char **arg)
{
    if(arg)
    {
        env[1].name = "sdfsF";
        env[1].value = "itekir";
    }
}