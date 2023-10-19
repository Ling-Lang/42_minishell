/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:16:36 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/19 11:31:56 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *home_dir;
void handlectrl(int signum)
{
    (void)signum;
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    ft_printf(BLU"\n>> "WHT);
}
int main()
{
    char *str;
    char **arg;
    home_dir = getenv("HOME");
    signal(SIGINT, handlectrl);
    while((str = readline(BLU">> "WHT)))
    {

        str[strcspn(str, "\n")] = '\0';
        if(str[0] == '\0')
        {
            continue;
        }
        if(str[0] != '\0')
            add_history(str);
        ft_wait_for_cmd(str);
    }
}
