/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:07:53 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/02 13:59:00 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_token	*init_tokens(char *str)
{
	t_token	*tokens;
	int		len;
	t_token	*new_token;

	tokens = NULL;
	len = 0;
	while (*str)
	{
		while (*str == ' ' && *str)
			str++;
		len = get_token_len(str);
		if (!len)
			break ;
		new_token = create_token(str, len);
		add_token(&tokens, new_token);
		str = str + len;
	}
	add_token(&tokens, create_token(NULL, 0));
	return (tokens);
}

t_token	*create_token(char *str, int len)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
	{
		perror("minishell");
		exit(1);
	}
	token->type = get_token_type(str, len);
	token->value = (char *)malloc(len + 1);
	if (token->value == NULL)
	{
		perror("minishell");
		exit(1);
	}
	if(!str || len == 0)
	{
		token->value = NULL;
		token->next = NULL;
		return (token);
	}
	ft_strncpy(str, (char *)(token->value), len);
	((char *)(token->value))[len] = '\0';
	token->next = NULL;
	return (token);
}
