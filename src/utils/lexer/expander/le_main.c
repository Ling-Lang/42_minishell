/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:42:18 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/11 16:04:44 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

char *ft_expand_var(t_token *token, t_env *env)
{
    char *var;
    
    var = get_env(ft_substr((const char *)token->value, 1, ft_strlen((const char *)token->value) - 1), env);
    // ft_printf("%s\n", var);
    return var;
} 

void ft_check_for_var(t_token **input, t_env *env)
{
    t_token *tmp = *input;
    int i = 0;

    while (tmp->next)
    {
        if (*((char *)tmp->value) == '$')
        {
            // ft_printf("Found var\n");
            char *expanded_value = ft_expand_var(tmp, env);
            free(tmp->value); // Assuming you need to free the old value
            tmp->value = expanded_value;
            break;
        }
        i++;
        tmp = tmp->next;
    }
}

