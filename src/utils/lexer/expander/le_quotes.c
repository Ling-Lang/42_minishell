/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:14:13 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/27 03:04:26 by ahocuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

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

char	*ft_get_env_name(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ft_isalnum(str[i]) == 1)
		i++;
	ret = ft_substr(str, 0, i);
	return (ret);
}

bool	ft_find_var(char *name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->name, name))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

char	*ft_check_for_var(char *str, t_env *env, int l_ret)
{
	int		i;
	char	*tmp;
	t_env	*tmp_e;
	int		var_start;
	char	*sub;
	char	*ret;
	int		j;

	ret = ft_strdup(str);
	i = 0;
	tmp = NULL;
	tmp_e = env;
	while (ret[i])
	{
		if (ret[i] == '$' && ret[i + 1] == '?')
		{
			var_start = i + 1;
			i += 2;
			sub = ft_strjoin(ft_strjoin(ft_substr(ret, 0, var_start - 1),
						ft_itoa(l_ret)), ft_substr(ret, i + 1, ft_strlen(ret)
						- i + 1));
			free(ret);
			ret = ft_strdup(sub);
			free(sub);
			i = var_start + ft_strlen(ft_itoa(l_ret)) - 1;
		}
		else if (ret[i] == '$' && ret[i + 1] != '\0')
		{
			var_start = i + 1;
			while (ret[i + 1] && (ft_isalnum(ret[i + 1]) || ret[i + 1] == '_'))
				i++;
			tmp = ft_substr(ret, var_start, (i - var_start + 1));
			if (ft_find_var(tmp, env))
			{
				sub = ft_strjoin((ft_strjoin(ft_substr(ret, 0, var_start - 1),
								get_env(tmp, tmp_e))), (ft_substr(ret, i + 1,
								ft_strlen(ret) - (i + 1))));
				free(ret);
				ret = ft_strdup(sub);
				free(sub);
				i = var_start + ft_strlen(get_env(tmp, tmp_e)) - 1;
			}
			free(tmp);
		}
		i++;
	}
	i = 0;
	while (ret[i])
	{
		if (ret[i] == '\"')
		{
			j = i;
			while (ret[j] != '\0')
			{
				ret[j] = ret[j + 1];
				j++;
			}
		}
		else
			i++;
	}
	return (ret);
}

char	*ft_rem_quotes(char *str, t_env *env, int l_ret)
{
	int		i;
	int		inside;
	int		j;
	char	*ret;
	char	*tmp;
	int		k;

	i = 0;
	inside = 0;
	j = 0;
	ret = (char *)malloc(sizeof(char) * (ft_str_len_quotes(str) + 1));
	while (str[i])
	{
		if (inside == 0 && (str[i] == '\'' || str[i] == '\"'))
		{
			if (str[i] == '\"')
			{
				tmp = ft_check_for_var(&str[i + 1], env, l_ret);
				k = 0;
				while (tmp[k])
					ret[j++] = tmp[k++];
				i += k;
				free(tmp);
			}
			inside = 1;
			i++;
		}
		else if (inside == 1 && (str[i] == '\'' || str[i] == '\"'))
		{
			inside = 0;
			i++;
		}
		else
			ret[j++] = str[i++];
	}
	ret[j] = '\0';
	return (ret);
}
