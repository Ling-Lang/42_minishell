/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_clean.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:09:18 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/14 16:16:28 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void free_tree(t_node **node)
{
    if(*node)
    {
        free_tree(&(*node)->l);
        free_tree(&(*node)->r);
        if(!(*node)->l && !(*node)->r)
        {
            free((*node)->data);
            free(*node);
            *node = NULL;
        }
    }
}
void clear_token(t_token *token)
{
    t_token *n;
    while(token)
    {
        n = token->next;
        free(token->value);
        free(token);
        token = n;
    }
    token = NULL;
}
void clean_parser(t_node **tree, t_stack *stack, t_token *input, int r)
{
    if(r == ERR)
        free_tree(tree);
    clear_stack(stack);
    clear_token(input);
}