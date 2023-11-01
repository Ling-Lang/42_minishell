/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:01:28 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/25 12:47:46 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
/* TODO Builtins
*Implement following builtins:
*export with no options
*unset with no options
*env with no options
*/

/* CHORE Norminette */
void ft_free(char ***arg)
{
    int i = 0;
    while((*arg)[i] != NULL)
    {
        free((*arg)[i]);
        i++;
    }
    free(*arg);
}
void ft_exit(char ***arg)
{
    // ft_printf("Test");
    ft_free(arg);
    exit(EXIT_SUCCESS); 
}
void ft_parse(char *str, t_env *env)
{
    char **arg;
    t_token *tokens;
	t_token	*cur;
	t_token	*temp;
    
    tokens = init_tokens(str);
    cur = tokens;
	while (cur)
	{
		printf("Type: %d, Value: %s\n", cur->type, (char *)cur->value);
		cur = cur->next;
	}
	// Don't forget to free the allocated memory when you're done.
	cur = tokens;
	while (cur)
	{
		temp = cur;
		cur = cur->next;
		free(temp->value);
		free(temp);
	}
    // arg = ft_new_split(str);
    // ft_printf("%s", arg[0]);
    // if(ft_strcmp(arg[0], "exit") == 0)
        // ft_exit(&arg);
    // ft_cmd_new(tokens);
}

void ft_cmd_new(t_token *token)
{
    ft_printf("%s\n", token->value);
    if(token->type == WORD)
    {
        if(ft_strcmp(token->value, "pwd") == 0)
            ft_pwd();
        else if(ft_strcmp(token->value, "cd") == 0)
            ft_new_cd(token);
    }
    else
        ft_printf("Wellp\n");
}
void ft_wait_for_cmd(char **arg, t_env *env)
{
    if(ft_strcmp(arg[0], "pwd") == 0)
        ft_pwd();
    else if(ft_strcmp(arg[0], "cd") == 0)
        ft_cd(arg);
    else if(ft_strcmp(arg[0], "clear") == 0)
        clear();
    else if (ft_strcmp(arg[0], "echo") == 0)
        ft_echo(arg);
    else if(ft_strcmp(arg[0], "export") == 0)
        ft_export(env, arg);
    else if(ft_strcmp(arg[0], "unset") == 0)
        ;
    else if(ft_strcmp(arg[0], "env") == 0)
        ft_env(env);
    else
        execute_command(arg);
}
