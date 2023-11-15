/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:42:18 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/15 17:53:21 by jkulka           ###   ########.fr       */
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
	// ft_printf("%s\n", var);
	return (var);
}
void	ft_handle_var(t_token **input, t_env *env)
{
	t_token	*tmp;
	char	*expanded_value;

	tmp = *input;
	while (tmp->next)
	{
		if (*((char *)tmp->value) == '$')
		{
			if (!ft_strcmp(tmp->value, "$?"))
				break ;
			expanded_value = ft_expand_var(tmp, env);
			free(tmp->value);
			tmp->value = ft_strdup(expanded_value);
			free(expanded_value);
			break ;
		}
		tmp = tmp->next;
	}
}

void ft_remove_quote(char **str, int *quote)
{
	char	*new_str;
	int		len;
	int		i;

	new_str = NULL;
	len = ft_strlen(*str);
	i = 0;
	if (len >= 2 && (((*str)[0] == '"' && (*str)[len - 1] == '"')))
	{
		// Double quotes
		*str = ft_strtrim((*str), "\"");
		*quote = 0;
	}
	else if (len >= 2 && ((*str)[0] == '\'' && (*str)[len - 1] == '\''))
	{
		*str = ft_strtrim((*str), "'");
		*quote = 1;
	}
	else
	{
		*quote = -1;
	}
    // ft_printf("%s\n", new_str);
}

void	ft_sanitize_tokens(t_token **input, t_env *env)
{
	t_token	*tmp;
	char	*value;
	int		quote;

	quote = 0;
	tmp = *input;
	while (tmp->next)
	{
		value = ft_strdup(tmp->value);
        ft_remove_quote(&value, &quote);
		free(tmp->value);
		tmp->value = ft_strdup(value);
		free(value);
		if (quote == 0 || quote == -1)
			ft_handle_var(&tmp, env);
		tmp = tmp->next;
	}
}
