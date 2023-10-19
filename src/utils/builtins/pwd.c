/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:16:19 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/19 12:17:32 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void ft_pwd(void)
{
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    ft_printf("%s\n", cwd);
}