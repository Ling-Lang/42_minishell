/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:08:50 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/23 22:44:55 by ahocuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void ft_export(t_env *env, char **arg)
{
    int i = 0;
    if(arg[1] == NULL)
    {
        while(env[i].name != NULL)
        {
            printf("%s=%s\n", env[i].name, env[i].value);
            i++;
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