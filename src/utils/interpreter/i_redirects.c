/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_redirects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:52:30 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/20 22:35:09 by ahocuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int ret_to(t_node *tree)
{
    int fd;
    fd = open(tree->r->r->data, O_RDWR | O_CREAT, 0666);
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

int handle_redirects2(t_node *tree, int r)
{
    if(!tree)
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
        if(tree->l->type == A_PIPE)
            return r;
    }
    return r;
}