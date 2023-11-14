/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:42:18 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/14 17:02:31 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

char *ft_expand_var(t_token *token, t_env *env)
{
    char *var;
    char *find;
    t_env *tmp;

    tmp = env;
    find = ft_substr((const char *)token->value, 1, ft_strlen((const char *)token->value));
    var = ft_strdup(get_env(find, tmp));
    free(find);
    // ft_printf("%s\n", var);
    return var;
} 

void ft_check_for_var(t_token **input, t_env *env)
{
    t_token *tmp;
    t_token *start;
    char *expanded_value;
    
    tmp = *input;
    int i = 0;
    while (tmp->next)
    {
        if (*((char *)tmp->value) == '$')
        {
            // ft_printf("Found var\n");
            expanded_value = ft_expand_var(tmp, env);
            // free(tmp->value); // Assuming you need to free the old value
            tmp->value = ft_strdup(expanded_value);
            free(expanded_value);
            
            break;
        }
        i++;
        tmp = tmp->next;
    }
    // tmp = start;
}

