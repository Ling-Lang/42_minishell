/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/23 14:22:19 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void clear()
{
    ft_printf("\033[H\033[J");
}

int execute_command(char **arg) {
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // Child process
        if (execvp(arg[0], arg) == -1) {
            perror("minishell");
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

char ** ft_str_copy(char **arg)
{
    char **res;
    int i;

    i = 0;
    while(arg[i] != NULL)
        i++;
    res = (char **)malloc(sizeof(char *) * (i + 1));
    if(!res)
        return NULL;
    i = 0;
    while(arg[i] != NULL)
    {
        res[i] = ft_strdup(arg[i]);
        if(!res[i])
        {
            while(i > 0)
            {
                free(res[i - 1]);
                i--;
            }
            free(res);
            return NULL;
        }
        i++;
    }
    res[i] = NULL;
    return res;
}
#include <string.h>
char *my_join(char *str1, char *str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char *result = (char *)malloc(len1 + len2 + 1);
    if (result) {
        strcpy(result, str1);
        strcpy(result + len1, str2);
    }
    return result;
}

char *ft_read_file(int fd)
{
    int BUFFER_SIZE = 42;
    char buffer[BUFFER_SIZE];
    char *res = "";
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        buffer[bytesRead] = '\0'; // Null-terminate the buffer.
        res = my_join(res, buffer);
    }
    // ft_printf("%s", res);
    return res;
}
/*TODO check if first arg is '<' then open and redirect to (arguments?) and execute command;
*
*/
// void ft_check_for_input_redirect(char **arg)
// {
//     bool redirect = false;
//     int i = 0;
//     int j = 0;
//     int fd = -1;
//     char *file;
//     int k = 0;
//     while(arg[k] != NULL)
//         k++;
//     if(ft_strcmp(arg[i], "<") == 0)
//         redirect = true;
//     if(redirect == true)
//     {
//         fd = open(arg[i + 1], O_RDONLY);
//         if(fd == -1)
//         {
//             perror("minishell");
//             return;
//         }
//         arg[k] = ft_read_file(fd);
//         ft_printf("%s", arg[k]);
//         // execute_command(arg);
//     }
//     else
//     {
//         ft_check_for_redirect(arg);
//     }
// }
void ft_check_for_redirect(char **arg)
{
    bool redirect = false;
    int output = -1;
    int i = 0;
    int j = 0;
    while(arg[i++] != NULL)
    {
        if(ft_strcmp(arg[i], ">") == 0)
        {
            redirect = true;
            output = open(arg[i + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            if(output == -1)
                break;
            j = i;
            while(arg[j] != NULL)
                arg[j++] = NULL;
            break;
        }
    }
    ft_redirect(arg, redirect, output);
}

void ft_redirect(char **arg, bool redirect, int fd)
{
    int standard_out;
    if(redirect)
    {
        standard_out = dup(1);
        if(dup2(fd, 1) == -1)
            perror("error");
        close(fd);
        ft_wait_for_cmd(arg);
        dup2(standard_out, 1);
        close(standard_out);
    }
    else
        ft_wait_for_cmd(arg);
}
