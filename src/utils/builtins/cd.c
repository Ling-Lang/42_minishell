/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:14:50 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/24 17:00:41 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void ft_cd(char **arg)
{
    char *home;

    home = getenv("HOME");
    if(!arg[1])
        chdir(home);
    chdir(arg[1]);
}
void ft_new_cd(t_token *token)
{
    char *home;
    t_token *tmp;
    
    tmp = token;
    home = getenv("HOME");
    if(token != NULL && token->next != NULL)
    {
        if(token->next->value != NULL)
            chdir(token->next->value);
        else
            chdir(home);
    }
    else
        chdir(home);
}