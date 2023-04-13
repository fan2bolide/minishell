/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:41:19 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 18:41:40 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

t_token	*evaluate_expression(char *expression, t_token *prev, int is_exec_name);
size_t	get_next_expression(char *command_line);
char	*create_token_content(char *expression);
void	log_token(t_token *token);
bool	check_all_consecutives_types(t_token_list *tokens);
bool	check_files_after_redirect(t_token_list *tokens);
bool	check_for_pipe_at_end(t_token_list *tokens);
bool	check_redirect_operators(t_token *token);

#endif
