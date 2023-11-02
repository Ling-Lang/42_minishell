/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:17:30 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/01 17:03:04 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "test.h"

void free_str_array(char **str)
{
    char **start;
    
    if(str)
    {
        start = str;
        while(*str)
        {
            free(*str);
            ++str;
        }
        free(start);
    }
}
int arg_len(char **arg)
{
    int i = 0;

    while(arg[i])
        i++;
    return i;
}
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

char **init_args(void)
{
    char **res;
    
    res = (char **)malloc(sizeof(*res));
    if(!res)
        return NULL;
    *res = NULL;
    return res;
}