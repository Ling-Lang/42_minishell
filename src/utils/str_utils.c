/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:28:05 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/17 13:23:31 by jkulka           ###   ########.fr       */
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
char *ft_last_word(char *str)
{
    int i = 0;
    int end;
    int start;
    char *dst;
    while(str[i] != '\0')
        i++;
    i--;
    while((str[i] == '\t' || str[i] == ' ') && i != 0)
        i--;
    end = i;
    while(str[i] != ' ' && str[i] != '\t' && i != 0)
        i--;
    if(str[i] == ' ' || str[i] == '\t')
        i++;
    start = i;
    dst = (char *)malloc(sizeof(char) * (end - start) + 1);
    dst = ft_strncpy(&str[start], dst, (end - start));
    return dst;
}
char *first_word(char *str)
{
    int i = 0;
    int start;
    int end;
    int j = 0;
    char *dst;
    while((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
        i++;
    start = i;
    while(str[i] && str[i] != '\t' && str[i] != ' ')
        i++;
    end = i- 1;
    dst = (char *)malloc(sizeof(char) * (end - start) + 1);
    ft_strncpy(&str[start], dst, (end - start));
    return dst;
}

int ft_wc(char *str)
{
    int i = 0;
    int wc = 0;
    while(str[i])
    {
        while(str[i] && (str[i] == ' ' || str[i] == '\t'))
            i++;
        if(str[i])
            wc++;
        while(str[i] && str[i] != '\t' && str[i] != ' ')
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
    
    res = (char **)malloc(sizeof(char *) * ft_wc(str) + 1);
    while(str[i])
    {
        while(str[i] != '\0' && (str[i] == ' ' || str[i] == '\t'))
            i++;
        j = i;
        while(str[i] && str[i] != '\t' && str[i] != ' ')
            i++;
        if(i > j)
        {
            res[k] = (char *)malloc(sizeof(char) * (i - j) + 1);
            ft_strncpy(&str[j], res[k], (i - j));
            k++;
        }
    }
    res[k] = NULL;
    return res;
}
