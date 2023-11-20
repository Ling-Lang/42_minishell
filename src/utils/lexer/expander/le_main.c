/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:42:18 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/20 15:15:30 by jkulka           ###   ########.fr       */
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
char *ft_get_last_ret(int l_ret)
{
	char *var;

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

void	ft_sanitize_tokens(t_token **input, t_env *env, int l_ret)
{
	t_token	*tmp;
	char	*value;
	char		quote;
	char *tmps;

	quote = 0;
	tmp = *input;
	while (tmp->next)
	{
		// value = ft_strdup(tmp->value);
		value = ft_rem_quotes(tmp->value, env, l_ret);
		// ft_printf("\t%s\n", tmps);
		free(tmp->value);
		tmp->value = ft_strdup(value);
		free(value);

		tmp = tmp->next;
	}
}
