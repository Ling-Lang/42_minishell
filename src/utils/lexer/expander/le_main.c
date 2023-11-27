/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:42:18 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/27 21:09:31 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

char	*ft_expand_var(t_token *token, t_env *env)
{
	char	*var;
	char	*find;
	t_env	*tmp;

	tmp = env;
	find = ft_substr((const char *)token->value, 1,
			ft_strlen((const char *)token->value));
	var = ft_strdup(get_env(find, tmp));
	free(find);
	return (var);
}

char	*ft_get_last_ret(int l_ret)
{
	char	*var;

	var = ft_strdup(ft_itoa(l_ret));
	return (var);
}

void	ft_handle_var(t_token **input, t_env *env, int l_ret)
{
	t_token	*tmp;
	char	*expanded_value;

	tmp = *input;
	while (tmp->next)
	{
		if (*((char *)tmp->value) == '$')
		{
			if (!ft_strcmp(tmp->value, "$?"))
				expanded_value = ft_get_last_ret(l_ret);
			else
				expanded_value = ft_expand_var(tmp, env);
			free(tmp->value);
			tmp->value = ft_strdup(expanded_value);
			free(expanded_value);
			break ;
		}
		tmp = tmp->next;
	}
}
int ft_get_var_len(char *str)
{
	int i;

	i = 1;
	if(str[0] == '$' && str[1] == '?')
	{
		// ft_printf("Hello\n");
		return (2);
	}
	while(str[i])
	{
		if(ft_isalnum(str[i]) || str[i] == '_')
			++i;
		else
			break;
	}
	return i;
}
char *ft_update_str(char *before, char *expanded, char *after, int len, int l_ret)
{
	char *res;
	char *s_1;
	if(!before || !after)
		return (NULL);
	if(len == 1)
	{
		s_1 = ft_strjoin(before, "$");
		if (!s_1)
			return NULL;
		res = ft_strjoin(s_1, after);
		free(s_1);
		return (res);
	}
	else if(!expanded)
		return(ft_strjoin(before, after));
	s_1 = ft_strjoin(before, expanded);
	if(!s_1)
		return(NULL);
	res = ft_strjoin(s_1, after);
	free(s_1);
	return (res);
}
char *ft_get_val(char *str, int len, t_env *env, int l_ret)
{
	char *org;
	char *res;
	t_env *tmp;
	tmp = env;
	org = (char *)malloc(sizeof(char)  * len);
	if(!org)
		return (NULL);
	ft_strlcpy(org, str + 1, len);
	org[len - 1] = 0;
	if(org[0] == '?')
		res = ft_itoa(l_ret);
	else
		res = get_env(org, tmp);
	free(org);
	return (res);
}
void ft_expander(char **str, t_env *env, int l_ret)
{
	int	i;
	int	len;
	char *before;
	char *res;
	char *tmp;
	i = -1;
	while((*str)[++i])
	{
		if ((*str)[i] == '$')
		{
			len = ft_get_var_len((*str + i));
			before = ft_substr(*str, 0, i);
			res = ft_substr(*str, i + len, ft_strlen(*str) - (i + len));
			tmp = *str;
			*str = ft_update_str(before, ft_get_val((*str + i), len, env, l_ret), res, len, l_ret);
			free(tmp);
			free(before);
			free(res);
			if(!*str)
				return ;
		}
	}
}


// void	ft_sanitize_tokens(t_token **input, t_env *env, int l_ret)
// {
// 	t_token	*tmp;
// 	char	*value;
// 	char	quote;
// 	char	*tmps;
// 	char *test;

// 	quote = 0;
// 	tmp = *input;
// 	while (tmp->next)
// 	{
// 		ft_expander(&tmp->value, env, l_ret);
// 		tmp = tmp->next;	
// 	}
// }

// void ft_sanitize_tokens(t_token **input, t_env *env, int l_ret) {
//     t_token *tmp;
//     char *value;
//     char quote;
//     char *tmps;
//     char *test;

//     quote = 0;
//     tmp = *input;
//     while (tmp->next) {
//         quote = 0; // Reset the quote flag for each token
//         for (int i = 0; tmp->value[; ++i) {
//             if (tmp->value == '"') {
//                 quote = (quote == 0) ? '"' : 0; // Toggle the quote flag for double quotes
//             } else if (tmp->value[i] == '\'') {
//                 quote = (quote == 0) ? '\'' : 0; // Don't consider single quotes
//             }
//         }
//         if (quote == 0 || quote == '"') { // If not in single quotes or in double quotes
//             ft_expander(&tmp->value, env, l_ret);
//         }
//         tmp = tmp->next;
//     }
// }


void ft_sanitize_tokens(t_token **input, t_env *env, int l_ret) {
    t_token *tmp = *input;

    while (tmp->next) {
        char *value = (char *)tmp->value;
        bool within_single_quotes = false;

        for (int i = 0; value[i]; ++i) {
            if (value[i] == '\'') {
                within_single_quotes = !within_single_quotes; // Toggle the single quotes flag
            } else if (value[i] == '$' && !within_single_quotes) {
                ft_expander(&value, env, l_ret);
                tmp->value = (void *)value; // Update the token value after expansion
                break; // Stop expansion for this token after encountering a $
            }
        }

        tmp = tmp->next;
    }
}
