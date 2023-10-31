/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_tokens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:06:28 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/31 13:48:44 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_token	*ft_tk_last(t_token *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_tk_add_back(t_token **token, t_token *new)
{
	t_token	*last;

	last = *token;
	if (*token == NULL)
	{
		*token = new;
		return ;
	}
	last = ft_tk_last(*token);
	last->next = new;
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (*tokens == NULL)
		*tokens = new_token;
	else
	{
		current = *tokens;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
}

int	get_token_type(char *str, int len)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * len + 1);
	ft_strncpy(str, tmp, len);
	if (!ft_strcmp(tmp, ">"))
		return (free(tmp), T_R_TO_FILE);
	else if (!ft_strcmp(tmp, "<"))
		return (free(tmp), T_R_FROM_FILE);
	else if (!ft_strcmp(tmp, "|"))
		return (free(tmp), T_PIPE);
	else if (!ft_strcmp(tmp, "<<"))
		return (free(tmp), T_LESS);
	else if (!ft_strcmp(tmp, ">>"))
		return (free(tmp), T_GREATER);
	else
		return (free(tmp), T_WORD);
}
