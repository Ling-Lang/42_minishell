/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:02:29 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/03 13:25:39 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int execute_builtin(char **arg)
{
    int r;
    
    r = 0;
    if(!ft_strcmp(arg[0], "cd"))
        r = ft_cd(arg);
    if(!ft_strcmp(arg[0], "pwd"))
        r = ft_pwd();
    if(!ft_strcmp(arg[0], "exit"))
        ft_exit(&arg);
    if(!ft_strcmp(arg[0], "echo"))
        ft_echo(arg);
    return r;
}