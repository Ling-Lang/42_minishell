/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:35:16 by ahocuk            #+#    #+#             */
/*   Updated: 2023/10/23 21:37:04 by ahocuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void ft_env(t_env *env)
{
    int i = 0;
    while(env[i].name != NULL)
    {
        printf("%s=%s\n", env[i].name, env[i].value);
        i++;
    }
}