/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:14:50 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/15 18:18:50 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int ft_cd(char **arg)
{
    char *home;
    home = getenv("HOME");
    // ft_printf("%d\n", ft_strlen(arg[1]));
    if(!arg[1])
        return(chdir(home));
    if(ft_strlen(arg[1]) == 0)
        return 0;
    if(opendir(arg[1]) != NULL)
        return(chdir(arg[1]));
    // perror("minishell: cd");
    ft_putstr_fd("minishell: cd: ", 2);
    perror(arg[1]);
    return(1);
}