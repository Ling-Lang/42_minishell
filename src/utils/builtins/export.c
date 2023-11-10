/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:08:50 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/10 05:31:14 by ahocuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// void ft_export(t_env *env, char **arg)
// {
//     int i = 0;
//     t_env *tmp;
//     tmp = env;
//     if(arg[1] == NULL)
//     {
//         while(tmp->next != NULL)
//         {
//             printf("%s=%s\n", tmp->name, tmp->value);
//             tmp = tmp->next;
//         }
//     }
//     else
//         ft_export_print(env, arg);
// }
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
    printf("absad\n");
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
        while(arg[i])
        {
            add_env(env, set_env(arg[i]));
            printf("ab\n");
            i++;
        }
    }
    return OK;
}



/*void ft_export_print(t_env *env, char **arg)
{
    if(arg)
    {
        env[1].name = "sdfsF";
        env[1].value = "itekir";
    }
}*/
