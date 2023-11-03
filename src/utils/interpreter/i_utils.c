/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:39:47 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/03 12:59:54 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char **init_args(void)
{
    char **res;
    
    res = (char **)malloc(sizeof(*res));
    if(!res)
        return NULL;
    *res = NULL;
    return res;
}

void free_str_array(char **str)
{
    char **start;
    
    if(str)
    {
        start = str;
        while(*str)
        {
            free(*str);
            ++str;
        }
        free(start);
    }
}
int arg_len(char **arg)
{
    int i = 0;

    while(arg[i])
        i++;
    return i;
}
int check_builtin(char *arg)
{
    if(!ft_strcmp(arg, "cd") || !ft_strcmp(arg, "export") || !ft_strcmp(arg, "echo") || !ft_strcmp(arg, "pwd") || !ft_strcmp(arg, "exit") || !ft_strcmp(arg, "unset") || !ft_strcmp(arg, "env"))
        return 1;
    return 0;
}