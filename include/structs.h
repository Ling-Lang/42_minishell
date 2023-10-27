/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:29:32 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/27 14:13:12 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
#include "minishell.h"

# define DEFAULT -1
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
    int d_quote;
    int s_quote;
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

typedef enum e_action
{
    NO_ACTION = -1,
    SHIFT = 0,
    REDUCE,
    ACCEPT,
    REJECT,
} t_action;

typedef enum e_rules
{
    PIPE_SEQUENCE = 500,
    SIMPLE_COMMAND,
    CMD_NAME,
    CMD_WORD,
    CMD_PREFIX,
    CMD_SUFFIX,
    IO_REDIRECT,
    IOFILE,
    FILENAME,
    IO_HERE,
    HERE_END,
} t_rules;
#endif