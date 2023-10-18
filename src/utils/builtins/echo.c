/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:07:09 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/18 13:10:30 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void ft_echo(char **arg)
{
    int i = 1;
    if(arg[1] == NULL)
    {
        ft_printf("\n");
        return;
    }
    if (arg[i] != NULL && ft_strcmp(arg[i], "-n") == 0) 
        i++;
    else if(ft_strcmp(arg[2], ">") == 0 && arg[3] != NULL)
    {
        int output = open(arg[3], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        ft_putstr_fd(arg[1], output);
        close(output);
        return;
    }
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
