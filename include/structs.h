/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:29:32 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/27 21:49:46 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "minishell.h"

# define DEFAULT -1
# define NO_ACTION -1
# define TO_PROMOTE 0
# define TO_CHILD 1
# define ROOT -2

typedef struct s_env
{
	const char		*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	int				type;
	void			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_quote
{
	int				d_quote;
	int				s_quote;
}					t_quote;
typedef enum e_pipe_ends
{
	READ_END,
	WRITE_END
}					t_pipe_ends;

typedef struct s_ptable
{
	int				state;
	int				token;
	int				action;
	int				n_state;
	int				reduce;
}					t_ptable;

typedef struct s_stack
{
	void			*data;
	int				type;
	int				state;
	struct s_stack	*next;
}					t_stack;

typedef struct s_node
{
	int				type;
	int				reduce;
	void			*data;
	struct s_node	*l;
	struct s_node	*r;
	struct s_node	*n;
}					t_node;

typedef enum e_ttype
{
	T_END = -2,
	T_WORD = 0,
	T_R_TO_FILE,
	T_R_FROM_FILE,
	T_GREATER,
	T_LESS,
	T_PIPE,
}					t_ttype;

typedef enum e_action
{
	SHIFT = 0,
	REDUCE,
	ACCEPT,
	REJECT,
}					t_action;

typedef enum e_rules
{
	R_PIPE_SEQUENCE = 500,
	R_SIMPLE_COMMAND,
	R_CMD_NAME,
	R_CMD_WORD,
	R_CMD_PREFIX,
	R_CMD_SUFFIX,
	R_IO_REDIRECT,
	R_IOFILE,
	R_FILENAME,
	R_IO_HERE,
	R_HERE_END,
}					t_rules;

typedef enum e_tree_types
{
	A_CMD = 0,
	A_R_TO_FILE,
	A_RET_FROM_FILE,
	A_GREATER,
	A_LESS,
	A_PIPE,
	A_PARAM,
	A_FILE,
	A_LIMITER
}					t_tree_types;

typedef enum e_fds
{
	READ,
	WRITE
}					t_fds;
#endif