/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:53:40 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/16 17:37:47 by jkulka           ###   ########.fr       */
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
        ft_handle_signals();
        ret = ft_execve(arg, env);
        free_str_array(arg);
        exit(ret);
    }
    else
    {
        ft_ignore_signals();
        wait_pid = waitpid(child_pid, &exit_code, 0);
        if(wait_pid == ERR)
            return (ERR);
    }
    return ft_get_exit_code(exit_code);
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
                r = execute_command(args, *env);
            if(!check_builtin(args[0]) && r > 0 && r < 128)
                ft_error(args[0], r);
        }
        free_str_array(args);
    }
    else
        r = ERR;
    if(fd[0] != -1)
        if(restore_fd(fd) == ERR)
            r = ERR;
    return r;
}
int exec_tree(t_node *tree, t_env **env)
{
    int r;
    int n;
    int fd[2];

    fd[0] = -1;
    r = 1;
    n = find_symbol(tree, A_PIPE, 0);
    if(n)
    {
        ft_printf("Found pipe \n");
        return 0;
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
