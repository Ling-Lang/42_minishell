/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:14:13 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/17 14:18:38 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int ft_str_len_quotes(char *str)
{
    int i = 0;
    int len = 0;
    int inside = 0;
    char q;

    q = 0;
    while(str[i])
    {
        if(inside == 0 && (str[i] == '\'' || str[i] == '\"'))
        {
            q = str[i];
            inside = 1;
            i++;
        }
        else if(inside == 1 && q == str[i])
        {
            inside = 0;
            q = 0;
            i++;
        }
        else{
        len++;
        i++;
        }
    }
    return len;
}

char *ft_rem_quotes(char *str, int len, char *q)
{
    int i = 0;
    char *ret;
    int inside = 0;
    int j = 0;

    ret = (char *)malloc(sizeof(char) * len + 1);
    if(!ret)
        return NULL;
    while(str[i])
    {
        if(inside == 0 && (str[i] == '\'' || str[i] == '\"'))
        {
            *q = str[i];
            inside = 1;
            i++;
        }
        else if(inside == 1 && *q == str[i])
        {
            inside = 0;
            i++;
        }
        else
        {
            ret[j] = str[i];
            i++;
            j++;
        }
    }
    ret[j] = '\0';
    return (ret);
}
