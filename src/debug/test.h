/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:09:26 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/27 16:19:34 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
#define TEST_H

const char *ttype_names[] = {
    "END",
    "WORD",
    "R_TO_FILE",
    "R_FROM_FILE",
    "GREATER",
    "LESS",
    "PIPE"
};

const char *e_action_names[] = {
    "NO_ACTION",
    "SHIFT",
    "REDUCE",
    "REJECT",
};
const char *e_rule_names[] = {
    "PIPE_SEQUENCE",
    "SIMPLE_COMMAND",
    "CMD_NAME",
    "CMD_WORD",
    "CMD_PREFIX",
    "CMD_SUFFIX",
    "IO_REDIRECT",
    "IOFILE",
    "FILENAME",
    "IO_HERE",
    "HERE_END"
};
typedef struct e_ptable
{
    int state;
    int token;
    int action;
    int n_state;
    int reduce;
}   t_ptable;
#endif