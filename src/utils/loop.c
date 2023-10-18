/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:01:28 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/18 13:08:40 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//TODO Export unset env builtins
void ft_wait_for_cmd(char **arg)
{
    char cwd[PATH_MAX];
    
    if(ft_strcmp(arg[0], "exit") == 0)
    {
        free(arg);
        exit(EXIT_SUCCESS);
    }
    else if(ft_strcmp(arg[0], "pwd") == 0)
    {
        getcwd(cwd, sizeof(cwd));
        ft_printf("%s\n", cwd);
    }
    else if(ft_strcmp(arg[0], "cd") == 0)
    {
        if(!arg[1])
            chdir(home_dir);
        chdir(arg[1]);
    }
    else if(ft_strcmp(arg[0], "clear") == 0)
        clear();
    else if (ft_strcmp(arg[0], "echo") == 0)
    {
        ft_echo(arg);
    }
    else if(ft_strcmp(arg[0], "export") == 0)
    {
        ft_printf("%s", home_dir);
    }
    else
        execute_command(arg);
}
