/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:05:35 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/17 13:23:12 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int list_files()
{
    struct dirent *entry;
    DIR *dp = opendir("."); // Open the current directory

    if (dp == NULL) {
        perror("opendir");
        return -1;
    }

    while ((entry = readdir(dp)) != NULL) {
        ft_printf("%s\n", entry->d_name);
    }

    closedir(dp);
    return 0;
}

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
