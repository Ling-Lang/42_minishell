/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/19 12:06:21 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void clear()
{
    ft_printf("\033[H\033[J");
}

int execute_command(char **arg) {
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // Child process
        if (execvp(arg[0], arg) == -1) {
            perror("execvp");
            exit(1);
        }
    } else if (child_pid < 0) {
        perror("fork");
    } else {
        // Parent process
        waitpid(child_pid, NULL, 0);
    }
    return 0;
}
void ft_check_for_redirect(char **arg)
{
    int redirect = 0;
    int output;
    int i = 0;
    int j = 0;
    int sout;
    while(arg[i++] != NULL)
    {
        if(ft_strcmp(arg[i], ">") == 0)
        {
            redirect = 1;
            output = open(arg[i + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            if(output == -1)
                break;
            j = i;
            while(arg[j] != NULL)
                arg[j++] = NULL;
            break;
        }

    }
    if(redirect)
    {
        sout = dup(1);
        if(dup2(output, 1) == -1)
            perror("error");
        close(output);
        execute_command(arg);
        dup2(sout, 1);
        close(sout);
    }
    else
        execute_command(arg);
}
