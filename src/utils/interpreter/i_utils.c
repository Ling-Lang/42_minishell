/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:39:47 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/13 12:42:39 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char **init_args(void)
{
    char **res;
    
    res = (char **)malloc(sizeof(*res));
    if(!res)
        return NULL;
    *res = NULL;
    return res;
}

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
        ++i;
    return i;
}
int check_builtin(char *arg)
{
    
    // ft_printf("%s\n", arg);
    if(ft_strcmp(arg, "cd") == 0 || \
        ft_strcmp(arg, "export") == 0 || \
        ft_strcmp(arg, "echo") == 0 || \
        ft_strcmp(arg, "pwd") == 0 || \
        ft_strcmp(arg, "exit") == 0 || \
        ft_strcmp(arg, "unset") == 0 || \
        ft_strcmp(arg, "env") == 0)
        return 1;
    return 0;
}
int	find_symbol(t_node *tree, int to_find, int n)
{
	if (!tree)
		return (n);
	if (tree->type == to_find)
		++n;
	n = find_symbol(tree->l, to_find, n);
	n = find_symbol(tree->r, to_find, n);
	return (n);
}