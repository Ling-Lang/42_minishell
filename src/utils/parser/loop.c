/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:01:28 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/23 14:22:28 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
/* TODO Builtins
*Implement following builtins:
*export with no options
*unset with no options
*env with no options
*/

/* CHORE Norminette */
void ft_free(char ***arg)
{
    int i = 0;
    while((*arg)[i] != NULL)
    {
        free((*arg)[i]);
        i++;
    }
    free(*arg);
}
void ft_exit(char ***arg)
{
    // ft_printf("Test");
    ft_free(arg);
    exit(EXIT_SUCCESS);
}
void ft_parse(char *str)
{
    char **arg;
    
    arg = ft_new_split(str);
    if(ft_strcmp(arg[0], "exit") == 0)
        ft_exit(&arg);
    ft_check_for_redirect(arg);
    // ft_check_for_input_redirect(arg);
    // ft_wait_for_cmd(arg);
    ft_free(&arg);
}

void ft_wait_for_cmd(char **arg)
{
    // ft_printf("%s", arg[0]);
    const char *path;
    path = (const char *)getenv("PATH");
    if(ft_strcmp(arg[0], "pwd") == 0)
        ft_pwd();
    else if(ft_strcmp(arg[0], "cd") == 0)
        ft_cd(arg);
    else if(ft_strcmp(arg[0], "clear") == 0)
        clear();
    else if (ft_strcmp(arg[0], "echo") == 0)
        ft_echo(arg);
    else if(ft_strcmp(arg[0], "export") == 0)
        ft_export();
    else if(ft_strcmp(arg[0], "unset") == 0)
        ;
    else if(ft_strcmp(arg[0], "env") == 0)
        ;
    else
        execute_command(arg);
}
