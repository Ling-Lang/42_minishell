/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:16:36 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/24 12:40:09 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtins.h"
void handlectrl(int signum)
{
    (void)signum;
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    ft_printf(BLU"\n>> "WHT);
}
void print_var(char **envp)
{
    int i = 0;
    while(envp[i] != NULL)
    {
        printf("%d\t%s\n",i, envp[i]);
        i++;
    }
}
int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *str;
    t_env *env = ft_init(envp);
    signal(SIGINT, handlectrl);
    while((str = readline(BLU">> "WHT)))
    {
        if(str == NULL || str[0] == EOF)
        {
            ft_printf("exit");
            break;
        }
        str[strcspn(str, "\n")] = '\0';
        if(str[0] == '\0')
        {
            continue;
        }
        if(str[0] != '\0')
            add_history(str);
        ft_parse(str, env);
    }
}
