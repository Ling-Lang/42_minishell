/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:06:10 by ahocuk            #+#    #+#             */
/*   Updated: 2023/11/26 04:20:39 by ahocuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int ft_heredoc(t_node *tree, t_env **env) {
    int pipe_fd[2];
    int file_fd;
    pid_t child_pid;
    char **args;
    int i = 0;

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return ERR;
    }

    file_fd = open("heredoc_temp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (file_fd == -1) {
        perror("open");
        return ERR;
    }

    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        close(file_fd);
        return ERR;
    }

    if (child_pid == 0) {  
        close(pipe_fd[1]); 
        dup2(pipe_fd[0], STDIN_FILENO);  


        args = iterate_tree(tree, init_args());
        execute_command32(args, *env);
        close(pipe_fd[0]);
        close(file_fd);
        _exit(EXIT_SUCCESS);  
    } else {  
        close(pipe_fd[0]);  

        args = iterate_tree(tree, init_args());
        while (args[i] != NULL) {
            dprintf(file_fd, "%s", args[i]); 
            i++;
        }

        close(pipe_fd[1]);
        close(file_fd);

        int status;
        waitpid(child_pid, &status, 0);
        if (!WIFEXITED(status)) {
            fprintf(stderr, "Child process did not exit normally\n");
            return ERR;
        }
    }

    //free_str_array2(args);
    return OK;
}

void free_str_array2(char **array) {
    for (int i = 0; array[i] != NULL; ++i) {
        free(array[i]);
    }
    free(array);
}

void execute_command32(char **args, t_env *env) {
    pid_t child_pid;
    pid_t wait_pid;
    int exit_code;

    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {  

        int ret = execve(args[0], args, t_env_to_envp(env));
        if (ret == -1) {
            return;
        }
    } else { 
        wait_pid = waitpid(child_pid, &exit_code, 0);
        if (wait_pid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }
}


void set_environment(t_env *env) {
    while (env != NULL) {
        setenv(env->name, env->value, 1);
        env = env->next;
    }
}