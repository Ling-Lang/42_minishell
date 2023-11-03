/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:16:36 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/03 12:33:46 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtins.h"
void handlectrl(int signum)
{
    (void)signum;
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    ft_printf(BLU"\n>> "WHT);
}
void print_var(char **envp)
{
    int i = 0;
    while(envp[i] != NULL)
    {
        printf("%d\t%s\n",i, envp[i]);
        i++;
    }
}
const char *ttype_names[] = {
    "END",
    "WORD",
    "R_TO_FILE",
    "R_FROM_FILE",
    "GREATER",
    "LESS",
    "PIPE"
};
void ft_print_tokens(t_token *token)
{
	t_token *cur;
	cur = token;
	while(cur)
	{
		ft_printf("Type: %d, Value: %s\n", cur->type, (char *)cur->value);
		cur = cur->next;
	}
}
int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *str;
    t_ptable **table = init_table();
    t_env *env;
    t_token *input;
    t_node *ast;
    char **args;
    ft_init(envp, &env);
    signal(SIGINT, handlectrl);
    while((str = readline(BLU">> "WHT)))
    {
        if(str == NULL || str[0] == EOF)
        {
            ft_printf("exit");
            break;
        }
        str[strcspn(str, "\n")] = '\0';
        if(str[0] == '\0')
            continue;
        if(str[0] != '\0')
            add_history(str);
        input = init_tokens(str);
        ft_print_tokens(input);
        ast = parser(input, table);
        args = iterate_tree(ast, init_args());
        // ft_printf("%s", args[0]);
        // execvp(args[0], args);
        exec_tree(ast, envp);
        free_tree(&ast);
    }
}
