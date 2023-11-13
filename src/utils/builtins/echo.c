/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:07:09 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/13 13:28:06 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void ft_echo(char **arg)
{
    // ft_printf("%s", arg[1]);
    int i = 1;
    if(arg[1] == NULL)
    {
        ft_printf("\n");
        return;
    }
    if (arg[i] != NULL && ft_strcmp(arg[i], "-n") == 0) 
        i++;
    while (arg[i] != NULL) 
    {
        ft_printf("%s", arg[i]);
        if (arg[i + 1] != NULL)
            ft_printf(" ");
        i++;
    }
    if (arg[1] != NULL && ft_strcmp(arg[1], "-n") != 0) 
        ft_printf("\n");
}
