/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:42:18 by jkulka            #+#    #+#             */
/*   Updated: 2023/12/01 14:28:18 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

char	*ft_update_str(char *before, char *expanded, char *after, int len)
{
	char	*res;
	char	*s_1;

	if (!before || !after)
		return (NULL);
	if (len == 1)
	{
		s_1 = ft_strjoin(before, "$");
		if (!s_1)
			return (NULL);
		res = ft_strjoin(s_1, after);
		free(s_1);
		return (res);
	}
	else if (!expanded)
		return (ft_strjoin(before, after));
	s_1 = ft_strjoin(before, expanded);
	if (!s_1)
		return (NULL);
	res = ft_strjoin(s_1, after);
	free(s_1);
	return (res);
}

void	ft_expander(char **str, t_env *env, int l_ret)
{
	int		i;
	int		len;
	char	*before;
	char	*res;
	char	*tmp;
	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '$')
		{
			len = ft_get_var_len((*str + i));
			before = ft_substr(*str, 0, i);
			tmp = ft_get_val((*str + i), len, env, l_ret);
			res = ft_substr(*str, i + len, ft_strlen(*str) - (i + len));
			*str = ft_update_str(before, tmp, res, len);
			free(before);
			free(tmp);
			free(res);
			if (!*str)
				return ;
		}
	}
}

int	ft_str_len_quotes(char *str)
{
	int		i;
	int		len;
	int		inside;
	char	q;

	i = -1;
	len = 0;
	inside = 0;
	q = 0;
	while (str[++i])
	{
		if (inside == 0 && (str[i] == '\'' || str[i] == '\"'))
		{
			q = str[i];
			inside = 1;
		}
		else if (inside == 1 && q == str[i])
		{
			inside = 0;
			q = 0;
		}
		else
			len++;
	}
	return (len);
}

char	*ft_rem_quotes(char *str)
{
	int		i;
	int		inside;
	int		j;
	char	*ret;

	i = -1;
	inside = 0;
	j = 0;
	ret = (char *)malloc(sizeof(char) * (ft_str_len_quotes(str) + 1));
	while (str[++i])
	{
		if (inside == 0 && (str[i] == '\'' || str[i] == '\"'))
			inside = 1;
		else if (inside == 1 && (str[i] == '\'' || str[i] == '\"'))
			inside = 0;
		else
			ret[j++] = str[i];
	}
	ret[j] = '\0';
	return (ret);
}

void	ft_sanitize_tokens(t_token **input, t_env *env, int l_ret)
{
	t_token	*tmp;
	char	*value;
	bool	within_single_quotes;
	int		i;

	within_single_quotes = false;
	tmp = *input;
	while (tmp->next)
	{
		i = -1;
		value = (char *)tmp->value;
		while (value[++i])
		{
			if (value[i] == '\'')
				within_single_quotes = !within_single_quotes;
			else if (within_single_quotes == false)
			{
				ft_expander(&(&value)[i], env, l_ret);
				value = ft_rem_quotes(value);
				free(tmp->value);
				tmp->value = ft_strdup(value);
				free(value);
				break ;
			}
		}
		value = ft_rem_quotes(value);
		free(tmp->value);
		tmp->value = ft_strdup(value);
		free(value);
		tmp = tmp->next;
	}
}
