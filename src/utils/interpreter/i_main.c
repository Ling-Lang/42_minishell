/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:38:35 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/03 13:07:19 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char **add_arg_back(char **arg, char *data)
{
    int i;
    char **res;
    if(!arg)
        return NULL;
    res = (char **)malloc(sizeof(*res) * arg_len(arg) + 2);
    if(!res)
        return(free_str_array(arg), NULL);
    i = -1;
    while(arg[++i])
    {
        res[i] = ft_strdup(arg[i]);
        if(!res[i])
        {
            free_str_array(arg);
            return(free_str_array(res), NULL);
        }
    }
    free_str_array(arg);
    res[i] = ft_strdup(data);
    if(!res[i])
        return (free_str_array(res), NULL);
    res[i + 1] = NULL;
    return (res);
}

char **add_cmd(char **args, t_node *node)
{
    int i;
    int j;
    char **split;
    
    split = ft_split(node->data, ' ');
    if(!split)
        return NULL;
    i = -1;
    while(split[++i])
    {
        args = add_arg_back(args, split[i]);
        if(!args)
        {
            j = -1;
            while(split[++j])
                free(split[j]);
            free(split[j]);
            return NULL;
        }
    }
    j = -1;
    while(split[++j])
        free(split[j]);
    free(split[j]);
    return args;
}
char **iterate_tree(t_node *node, char **args)
{
    if(!args || !node || (node && node->type == A_PIPE))
        return args;
    args = iterate_tree(node->l, args);
    args = iterate_tree(node->r, args);
    if(node->type == A_PARAM || node->type == A_CMD)
    {
        if(node->type == A_CMD && ft_strchr(node->data, ' '))
            args = add_cmd(args, node);
        else
            args = add_arg_back(args, node->data);
    }
    return args;
}
int find_symbol(t_node *tree, int to_find, int n)
{
    if(!tree)
        return n;
    if(tree->type == to_find)
        n++;
    n = find_symbol(tree->l, to_find, n);
    n = find_symbol(tree->r, to_find, n);
    return n;
}

void cache_fd(int *fd)
{
    fd[0] = dup(STDIN_FILENO);
    fd[1] = dup(STDOUT_FILENO);
}
int ret_to(t_node *tree)
{
    int fd;
    ft_printf("Here\n");
    fd = open(tree->r->r->data, O_RDWR | O_CREAT, 0666);
    ft_printf("Here\n");
    if(fd == ERR)
        return(perror(tree->r->r->data), ERR);
    if(dup2(fd, STDOUT_FILENO) == ERR)
        return(perror("minishell"), ERR);
    return 0;
}

int append_to(t_node *tree)
{
    int fd;

    fd = open(tree->r->r->data, O_RDWR | O_CREAT | O_APPEND, 0666);
    if(fd == ERR)
        return(perror(tree->r->r->data), ERR);
    if(dup2(fd, STDOUT_FILENO) == ERR)
        return(perror("minishell"), ERR);
    return 0;
}
int ret_from(t_node *tree)
{
    int fd;

    fd = open(tree->r->r->data, O_RDONLY);
    if(fd == ERR)
        return(perror(tree->r->r->data), ERR);
    if(dup2(fd, STDIN_FILENO) == ERR)
        return(perror("minishell"), ERR);
    return 0;
}

int handle_redirects(t_node *tree, int r)
{
    if(!tree || (tree && tree->type == A_PIPE))
        return r;
    r = handle_redirects(tree->l, r);
    r = handle_redirects(tree->r, r);
    if(r == ERR)
        return ERR;
    if(tree->reduce == R_IOFILE)
    {
        if(tree->l->type == A_R_TO_FILE)
            r = ret_to(tree);
        if(tree->l->type == A_RET_FROM_FILE)
            r = ret_from(tree);
        if(tree->l->type == A_GREATER)
            r = append_to(tree);
    }
    return r;
}
int execute_command(char **arg, char **envp)
{
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
int restore_fd(int *fd)
{
    fd[0] = dup2(fd[0], STDIN_FILENO);
    fd[1] = dup2(fd[1], STDOUT_FILENO);
    return 1;
}
int simple_command(t_node *tree, int *fd, char **envp)
{
    char **args;
    int r;
    
    r = 0;
    args = iterate_tree(tree, init_args());
    if(check_builtin(args[0]))
        r = execute_builtin(args);
    else
       r = execute_command(args, envp);
    if(fd[0] != -1)
        restore_fd(fd);
    return r;
}
int exec_tree(t_node *tree, char **envp)
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
            r = simple_command(tree, fd, envp);
    }
    return 1;
}