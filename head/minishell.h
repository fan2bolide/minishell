//
// Created by basil jeannot on 24/02/2023.
//

#ifndef MINISHELL_MINISHELL_H
# define MINISHELL_MINISHELL_H

# include "execute_cmd_line.h"
# include "lexer.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

t_list		*get_sample_tokens(); //debug
t_to_exec	*convert_token_lst_into_to_exec_lst(t_list *token_lst);

# define SPEC_CHAR "><|&"
#endif
