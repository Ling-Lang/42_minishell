/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:53:40 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/07 18:46:45 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int execute_command(char **arg, t_env *env)
{
    pid_t child_pid = fork();
    get_bin(&arg[0], env);
    char **envp;

    ft_printf("bin: %s", arg[0]);
    envp = t_env_to_envp(env);
    if(!envp)
        return ERR;
    if (child_pid == 0)
    {
        if (execve(arg[0], arg, envp) == -1) 
        {
            perror("minishell");
            exit(1);
        }
    }
    else if (child_pid < 0) 
        perror("fork");
    else
        waitpid(child_pid, NULL, 0);
    return 0;
}
int simple_command(t_node *tree, int *fd, t_env *env)
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
                r = execute_builtin(args);
            else
                r = execute_command(args, env);
        }
        free_str_array(args);
    }
    if(fd[0] != -1)
        restore_fd(fd);
    return r;
}
int exec_tree(t_node *tree, t_env *env)
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
        cache_fd(fd);
        if(handle_redirects(tree, 0) != ERR)
            r = simple_command(tree, fd, env);
    }
    return r;
}