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

t_list	*convert_token_lst_into_to_exec_lst(t_list *token_lst);
int		token_cmd_line_size(t_list *token_lst);
//debug
t_list		*get_sample_tokens();
void	log_token(struct s_token *token);
void	log_token_list(t_list *token_list);
void	log_to_exec_lst(t_list *to_exec_list);
void	log_to_exec(t_to_exec *to_exec);
# define SPEC_CHAR "<>|&$"
#endif
