/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <ba...@student.42lyon.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:43:37 by bajeanno          #+#    #+#             */
/*   Updated: 2023/03/06 15:00:00 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_MINISHELL_H
# define MINISHELL_MINISHELL_H

# include "execute_cmd_line.h"
# include "lexer.h"
# include "expand_token.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

t_list	*convert_token_lst_into_cmd_lst(t_list *token_lst, char **envp);
int		token_cmd_line_size(t_list *token_lst);
//debug
t_list	*get_sample_tokens();
t_list	*token_parsing(t_list *tokens);
void	log_token_list(t_list *token_list);
void	log_cmd_lst(t_list *cmd_list);
void	log_cmd(t_cmd *cmd);
# define SPEC_CHAR "<>|&$"
#endif
