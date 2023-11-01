/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:57:00 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/01 18:56:00 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_init(char **envp, t_env **env)
{
    int i = 0;
    char **tmp;
    while(envp[i] != NULL)
        i++;
    *env = (t_env *)malloc(sizeof(t_env) * i);
    if(!env)
        return ;
    i = 0;
    while(envp[i] != NULL)
    {
        tmp = ft_split(envp[i], '=');
        (*env)[i].name = (const char *)malloc(sizeof(char) * (ft_strlen(tmp[0]) + 1));   
        (*env)[i].value = (char *)malloc(sizeof(char) * (ft_strlen(tmp[1]) + 1));  
        (*env)[i].name = tmp[0]; 
        (*env)[i].value = tmp[1]; 
        i++;
    }
    
}