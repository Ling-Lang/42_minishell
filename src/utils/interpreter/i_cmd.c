/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:53:40 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/26 04:19:49 by ahocuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int ft_execve(char **args, t_env *env)
{
    int ret;
    char **envp;
    
    if(get_bin(&args[0], env) == ERR)
        return (ERR);
    envp = t_env_to_envp(env);
    if(!envp)
        return (ERR);
    ret = execve(args[0], args, envp);
    if(ret == ERR)
    {
        if(errno == EAGAIN)
            ret = 126;
        else
            ret = 127;
    }
    return (ret);
}

int execute_command(char **arg, t_env *env)
{
    pid_t child_pid;
    pid_t wait_pid;
    int ret;
    int exit_code;
    
    child_pid = fork();
    if(child_pid == ERR)
        return (ERR);
    if(child_pid == 0)
    {
        // ft_handle_signals();
        ret = ft_execve(arg, env);
        free_str_array(arg);
        exit(ret);
    }
    else
    {
        // ft_ignore_signals();
        wait_pid = waitpid(child_pid, &exit_code, 0);
        if(wait_pid == ERR)
            return (ERR);
    }
    return ft_get_exit_code(exit_code);
}

void execute_command2(char **args) {
    pid_t child_pid;
    int status;

    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {  // Child process
        
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {  // Parent process
        waitpid(child_pid, &status, 0);
    }
}

int simple_command(t_node *tree, int *fd, t_env **env)
{
    char **args;
    int r;
    r = 0;
    
    args = iterate_tree(tree, init_args());
    if(args)
    {
        if(args[0])
        {
            if(check_builtin(args[0]))
            {
                r = execute_builtin(args, env);
            }
            else
            {
                r = execute_command(args, *env);
            }
            if(!check_builtin(args[0]) && r > 0 && r < 128)
                ft_error(args[0], r);
        }
        //free_str_array(args);
    }
    else
        r = ERR;
    
    if(fd[0] != -1)
        if(restore_fd(fd) == ERR)
            r = ERR;
    return r;
}
void execute_piped_commands(char ****commands, int num_commands, t_env **env) {
    int prev_pipe_fd = -1;
    int pipe_fd[2];

    int i = 0;
    while (i < num_commands) {
        if (i < num_commands - 1) {
            if (pipe(pipe_fd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        pid_t child_pid = fork();
        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) {  // Child process
            if (prev_pipe_fd != -1) {
                dup2(prev_pipe_fd, STDIN_FILENO);
                close(prev_pipe_fd);
            }

            if (i < num_commands - 1) {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }

            if (strcmp((*commands)[i][0], "export") == 0) {
                // Handle export command here
                ft_export_special(commands, i, env);
            } else {
                execute_command2((*commands)[i]);
            }

            exit(EXIT_SUCCESS);
        } else {  // Parent process
            if (prev_pipe_fd != -1) {
                close(prev_pipe_fd);
            }

            if (i < num_commands - 1) {
                close(pipe_fd[1]);
                prev_pipe_fd = pipe_fd[0];
            }

            waitpid(child_pid, NULL, 0);
        }

        ++i;
    }
}

int simple_command2(t_node *tree, int *fd, t_env **env)
{
    char **args;
    char **tmp;
    char **tmp2;
    int r;
    r = 0;
    int a;
    a =0;
    int pipe;
    pipe = 1;
    char ***commands = NULL;
    int num_commands = 0;
    args = iterate_tree2(tree, init_args());
    while(args[a] != NULL)
    {
        if(strcmp(args[a], "|") == 0)
            pipe++;
        a++;
    }
    commands = (char ***)malloc(64 * sizeof(char **)); // 64 is max commands
    if (commands == NULL) 
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    while(args[0] != NULL)
    {
        tmp = copy_string_array(args);
        remove_pipe_symbol(tmp);
        commands[num_commands++] = tmp;
        while(check_builtin(args[0]) != 5 && args[0] != NULL)
            shift_elements(args, 0); 
        shift_elements(args, 0);
    }
    execute_piped_commands(&commands, num_commands, env);

    for (int i = 0; i < num_commands; ++i) {
        free(commands[i]);
    }
    free(commands);

    return 0;
    /*while (args[a]) // testing sm
    {
        if(strcmp(args[a], "grep") == 0)
        {
            a = a + 3; 
            if(args[a] == NULL || (strcmp(args[a], "|") == 0))
            {
                a = a - 5;
                if((strcmp(args[a], "ls") == 0) || (strcmp(args[a], "-l") == 0))
                {
                    tmp = copy_string_array(args);
                    remove_pipe_symbol(tmp);
                    while(check_builtin(args[0]) != 5)
                        shift_elements(args, 0);
                    shift_elements(args, 0);
                    tmp2 = copy_string_array(args);
                    remove_pipe_symbol(tmp2);
                    execute_pipe_commands(tmp, tmp2);
                    return r;
                }
            }

        }
        a++;
    }
    
    if(args)
    {
        while(args[0] != NULL)
        {
            if(check_builtin(args[0]) == 1)
            {
                tmp = copy_string_array(args);
                remove_pipe_symbol(tmp);
                r = execute_builtin(tmp, env);
                while(check_builtin(args[0]) != 5 && args[0] != NULL)
                    shift_elements(args, 0);
            }
            if(check_builtin(args[0]) == 5)
                shift_elements(args, 0);
            if(check_builtin(args[0]) == 0 && args[0] != NULL) 
            {  
                tmp = copy_string_array(args);
                remove_pipe_symbol(tmp);
                r = execute_command(tmp, *env);
                while(check_builtin(args[0]) != 5 && args[0] != NULL)
                    shift_elements(args, 0);
            }
        }
        free_str_array(args); 
    }
    else
        r = ERR;
    if(fd[0] != -1)
        if(restore_fd(fd) == ERR)
            r = ERR;
    return r; */
}

char** copy_string_array(char **original) 
{
    if (original == NULL)
        return NULL;

    int size; 
    size =  0;
    while (original[size] != NULL)
        size++;

    char **copy = (char **)malloc((size + 1) * sizeof(char *));
    if (copy == NULL) 
        return NULL;
    int i;
    i = 0;
    while (i <= size) 
    {
        if (original[i] != NULL) 
        {
            copy[i] = strdup(original[i]);
            if (copy[i] == NULL) 
            {
                free_string_array(copy);
                return NULL;
            }
        } 
        else 
            copy[i] = NULL;
        i++;
    }

    return copy;
}

void free_string_array(char **array) 
{
    if (array == NULL)
        return;

    int i;
    i = 0;
    while (array[i] != NULL)
    {
        free(array[i]);
        i++;
    }

    free(array);
}

void remove_pipe_symbol(char **args) {
    int i = 0;
    while (args[i] != NULL && strchr(args[i], '|') == NULL)
        ++i;

    if (args[i] != NULL) 
    {
        args[i] = NULL;
        while (args[++i] != NULL) 
            args[i] = NULL;
    }
}


void shift_elements(char **array, int position) 
{
    if (array == NULL || position < 0) 
        return;
    
    if(array[position + 1] == NULL)
    {
        array[position] = NULL;
        return;
    }

    free(array[position]);

    while (array[position] = array[position + 1]) 
        ++position;
    array[position] = NULL;
}


int exec_tree(t_node *tree, t_env **env)
{
    int r;
    int n;
    int fd[2];
    int g;

    fd[0] = -1;
    r = 1;
    n = find_symbol(tree, A_PIPE, 0);
    g = find_symbol(tree, T_LESS, 0);
    if(g)
    {
        ft_heredoc(tree, env);
        return r;
    }
    if(n)
    {
        cache_fd((int *)fd);
        if(handle_redirects2(tree, 0) != ERR)
        {
            r = simple_command2(tree, fd, env);
        }
        ft_printf("Found pipe \n");
        //return 0;
    }
    else
    {
        cache_fd((int *)fd);
        if(handle_redirects(tree, 0) != ERR)
        {
            r = simple_command(tree, fd, env);
        }
    }
    return r;
}
