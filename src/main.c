/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:16:36 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/17 13:07:17 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
int main()
{
    char *str;
    char **arg;
    home_dir = getenv("HOME");
    while((str = readline(">> ")))
    {
        str[strcspn(str, "\n")] = '\0';
        if(str[0] == '\0')
        {
            free(str);
            continue;
        }
        arg = ft_new_split(str);
        ft_wait_for_cmd(arg);
    }
}
