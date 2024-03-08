/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:42:18 by jkulka            #+#    #+#             */
/*   Updated: 2024/03/08 13:57:35 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
		res = ft_strjoin_free(s_1, after);
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
			tmp = *str;
			res = ft_substr(*str, i + len, ft_strlen(*str) - (i + len));
			*str = ft_update_str(before, ft_get_val((*str + i), len, env,
						l_ret), res, len);
			free(before);
			free(tmp);
			free(res);
			if (!*str)
				return ;
		}
	}
}

void	ft_sanitize_tokens(t_token **input, t_env *env, int l_ret)
{
	t_token	*tmp;
	char	*value;
	bool	within_single_quotes;
	int		i;

	within_single_quotes = false;
	tmp = *input;
	value = NULL;
	while (tmp->next)
	{
		i = -1;
		value = ft_strdup(tmp->value);
		while (value[++i])
		{
			if (value[i] == '\'')
				within_single_quotes = !within_single_quotes;
			else if (within_single_quotes == false)
			{
				ft_expander(&(&value)[i], env, l_ret);
				break ;
			}
		}
		copy_value(&tmp, &value);
	}
}
