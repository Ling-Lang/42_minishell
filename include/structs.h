/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:29:32 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/25 13:05:41 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
#include "minishell.h"

typedef struct s_env
{
    const char *name;
    char *value;
} t_env;

typedef struct s_token
{
    int type;
    void *value;
    struct s_token *next;
} t_token;

typedef struct s_quote
{
    int double_quote;
    int single_quote;
} t_quote;

typedef enum e_ttype
{
    END = -2,
    WORD = 0,
    R_TO_FILE,
    R_FROM_FILE,
    GREATER,
    LESS,
    PIPE,
} t_ttype;

#endif