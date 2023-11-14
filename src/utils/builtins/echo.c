/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:07:09 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/14 13:27:16 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// void ft_echo(char **arg)
// {
//     // ft_printf("%s", arg[1]);
//     int i = 1;
//     if(arg[1] == NULL)
//     {
//         ft_printf("\n");
//         return;
//     }
//     if (arg[i] != NULL && ft_strcmp(arg[i], "-n") == 0) 
//         i++;
//     while (arg[i] != NULL) 
//     {
//         ft_printf("%s", arg[i]);
//         if (arg[i + 1] != NULL)
//             ft_printf(" ");
//         i++;
//     }
//     if (arg[1] != NULL && ft_strcmp(arg[1], "-n") != 0) 
//         ft_printf("\n");
// }
//Look if cur str has -n only or -n and after the n no other than n -nn == -n -na != -n

bool ft_check_n(char *str)
{
    int i;
    if(!ft_strcmp(str, "-n"))
        return (true);
    if(str[0] == '-' && str[1] == 'n')
    {
        i = 1;
        while(str[++i])
        {
            if(str[i] != 'n')
                return (false);
        }
        return (true);
    }
    return (false);
}

int ft_echo(char **arg, int argc)
{
    int i;
    bool has_flag;
    bool start;
    
    start = true;
    has_flag = false;
    i = 0;
    // ft_printf("%s", "test");
    while(arg[++i] && ft_check_n(arg[i]))
        has_flag = true;
    while(i < argc)
    {
        if(!start)
            ft_putchar_fd(' ', 1);
        ft_putstr_fd(arg[i], 1);
        if(start)
            start = false;
        ++i;
    }
    if(argc >= 1 && !has_flag)
        ft_putchar_fd('\n', 1);
    return 0;
}