/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:07:09 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/26 19:13:25 by ahocuk           ###   ########.fr       */
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
    int a;
    
    start = true;
    has_flag = false;
    i = 0;
    if(!ft_strcmp(arg[1], "$?"))
    {
        ft_printf("%d", 0);
        return 0;
    }
    if(contains_symbol(arg, '$'))
    {
        a = contains_symbol(arg, '$');
        if(!ft_strcmp(arg[a], "$PWD"))
            return(ft_pwd());
        return 0;
    }
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

int contains_symbol(char **args, char symbol) 
{
    int i;
    i = 0;
    while (*args != NULL) 
    {
        char *arg = *args;
        while (*arg != '\0') 
        {
            if (*arg == symbol) 
            {
                ++arg;
                if(*arg == ' ')
                    return 0;
                return (i);
            }
            ++arg;
        }
        ++args;
        i++;
    }
    return 0; 
}