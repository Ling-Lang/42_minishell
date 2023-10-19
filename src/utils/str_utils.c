/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:28:05 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/19 11:28:43 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ft_strncpy(char *src, char *dst, int n)
{
    int i = 0;
    while(i < n)
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return dst;
}

int ft_wc(char *str)
{
    int i = 0;
    int wc = 0;
    while(str[i])
    {
        while(str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
            i++;
        if(str[i])
            wc++;
        while(str[i] && str[i] != '\t' && str[i] != ' ' && str[i] != '\n')
            i++;
    }
    return wc;
}

char **ft_new_split(char *str)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char **res;
    
    res = (char **)malloc(sizeof(char *) * (ft_wc(str) + 1));
    // ft_printf("%d", ft_wc(str));
    while(str[i])
    {
        while(str[i] != '\0' && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
            i++;
        j = i;
        while(str[i] && str[i] != '\t' && str[i] != ' ' && str[i] != '\n')
            i++;
        if(i > j)
        {
            res[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
            ft_strncpy(&str[j], res[k], (i - j));
            k++;
        }
    }
    res[k] = NULL;
    return res;
}
