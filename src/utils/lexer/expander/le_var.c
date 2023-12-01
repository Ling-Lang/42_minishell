/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:38:12 by jkulka            #+#    #+#             */
/*   Updated: 2023/12/01 14:30:24 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

char	*ft_get_val(char *str, int len, t_env *env, int l_ret)
{
	char	*org;
	char	*res;

	org = (char *)malloc(sizeof(char) * len);
	if (!org)
		return (NULL);
	ft_strlcpy(org, str + 1, len);
	org[len - 1] = 0;
	if (org[0] == '?')
		res = ft_itoa(l_ret);
	else
		res = get_env(org, env);
	free(org);
	return (res);
}

int	ft_get_var_len(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '$' && str[1] == '?')
		return (2);
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			++i;
		else
			break ;
	}
	return (i);
}

char	*ft_get_last_ret(int l_ret)
{
	char	*var;

	var = ft_strdup(ft_itoa(l_ret));
	return (var);
}
