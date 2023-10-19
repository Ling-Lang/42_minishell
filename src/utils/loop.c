/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:01:28 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/19 11:41:53 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/* TODO Builtins
*Implement following builtins:
*export with no options
*unset with no options
*env with no options
*/

/* CHORE Norminette */

void ft_wait_for_cmd(char *str)
{
    char **arg;
    
    arg = ft_new_split(str);
    char cwd[PATH_MAX];
    if(ft_strcmp(arg[0], "exit") == 0)
    {
        for (int i = 0; arg[i] != NULL; i++)
        {
            free(arg[i]);
        }
        free(arg);
        exit(EXIT_SUCCESS);
    }
    else if(ft_strcmp(arg[0], "pwd") == 0)
    {
        getcwd(cwd, sizeof(cwd));
        ft_printf("%s\n", cwd);
    }
    else if(ft_strcmp(arg[0], "cd") == 0)
        ft_cd(arg);
    else if(ft_strcmp(arg[0], "clear") == 0)
        clear();
    else if (ft_strcmp(arg[0], "echo") == 0)
        ft_echo(arg);
    else if(ft_strcmp(arg[0], "export") == 0)
        ft_printf("%s", home_dir);
    else
        execute_command(arg);
    for (int i = 0; arg[i] != NULL; i++)
    {
        free(arg[i]);
    }
    free(arg);
}
