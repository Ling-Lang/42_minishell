/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:02:29 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/14 13:26:42 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int execute_builtin(char **arg, t_env **env)
{
    int r;
    int i;
    
    i = 0;
    r = 0;
    while(arg[i])
        ++i;
    // ft_printf("%s\n", arg[0]);
    // write(1, "1\n", 1);
    if(!ft_strcmp(arg[0], "cd"))
        r = ft_cd(arg);
    if(!ft_strcmp(arg[0], "pwd"))
        r = ft_pwd();
    if(!ft_strcmp(arg[0], "exit"))
        ft_exit(&arg);
    if(!ft_strcmp(arg[0], "echo"))
        r = ft_echo(arg, i);
    if(!ft_strcmp(arg[0], "export"))
        ft_export(env, arg);
    if(!ft_strcmp(arg[0], "env"))
        ft_env(env);
    //if(!ft_strcmp(arg[0], "unset"))
       // ft_unset(env, arg);
    return r;
}