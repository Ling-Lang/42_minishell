/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:14:13 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/17 17:41:02 by jkulka           ###   ########.fr       */
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
char *ft_get_env_name(char *str)
{
    char *ret;
    int i = 0;
    int j = 0;
    while(ft_isalnum(str[i]) == 1)
        i++;
    ret = ft_substr(str, 0, i);
    return (ret);
}
bool ft_find_var(char *name, t_env *env)
{
    t_env *tmp;

    tmp = env;
    while(tmp->next)
    {
        if(!ft_strcmp(tmp->name, name))
            return true;
        tmp = tmp->next;
    }
    return false;
}
char * ft_check_for_var(char *str, t_env *env, int l_ret)
{
    int i = 0;
    int j = 0;
    char *ret;
    char *tmp;
    t_env *tmp_e;

    tmp_e = env;
    while(str[i] != '\"' && str[i])
    {
        if(str[i] == '$')
        {
            if(str[i] == '?')
                ret = ft_strdup(ft_itoa(l_ret));
            else
            {
                tmp = ft_get_env_name(&str[i + 1]);
                if(ft_find_var(tmp, env))
                    ret = ft_strjoin(ft_strjoin(ft_substr(str, 0, i), get_env(tmp, tmp_e))
                       , ft_substr(str, ft_strlen(tmp) + (i + 1), ft_strlen(str) - (ft_strlen(tmp) + (i + 2))));
                    
                else
                    free(tmp);
            }
            
        }
        i++;
    }
    // ft_printf("%s\n", ret);
    if(ret)
    {
        return ret;
    }
    return str;
}
char *ft_rem_quotes(char *str, char *q, t_env *env, int l_ret)
{
    int i = 0;
    char *ret;
    int inside = 0;
    int j = 0;
    char *tmp;
    int s_pos = 0;

    if(!ret)
        return NULL;
    while(str[i])
    {
        if(inside == 0 && (str[i] == '\'' || str[i] == '\"'))
        {
            if(str[i] == '\"')
            {
                tmp = ft_check_for_var(&str[i + 1], env, l_ret);
                // ret = ft_strdup(tmp);
                // j += ft_strlen(tmp);
                // ft_printf("\t%s\n", tmp);
            }
            *q = str[i];
            inside = 1;
            i++;
        }
        else if(inside == 1 && *q == str[i])
        {
            if(tmp)
                ret = ft_strjoin(ft_substr(str, s_pos, ft_strlen(tmp) - 1), tmp);
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
    // if(ft_strlen(ret) == 0)
    //     ret = ft_strdup(str);
    // ft_printf(tmp);
    ret[j] = '\0';
    return (ret);
}
