/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:02:29 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/13 13:53:18 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int execute_builtin(char **arg, t_env **env)
{
    int r;
    r = 0;
    // ft_printf("%s\n", arg[0]);
    // write(1, "1\n", 1);
    if(!ft_strcmp(arg[0], "cd"))
        r = ft_cd(arg);
    if(!ft_strcmp(arg[0], "pwd"))
        r = ft_pwd();
    if(!ft_strcmp(arg[0], "exit"))
        ft_exit(&arg);
    if(!ft_strcmp(arg[0], "echo"))
        ft_echo(arg);
    if(!ft_strcmp(arg[0], "export"))
        ft_export(env, arg);
    if(!ft_strcmp(arg[0], "env"))
        ft_env(env);
    //if(!ft_strcmp(arg[0], "unset"))
       // ft_unset(env, arg);
    return r;
}