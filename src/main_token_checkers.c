/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_token_checkers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 03:51:57 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/11 03:52:05 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	check_files_after_redirect(t_token_list *tokens)
{
	t_token_list	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->content->type == redirect_in || \
			curr->content->type == redirect_out_trunc || \
			curr->content->type == redirect_out_append || \
			curr->content->type == redirect_hd)
		{
			if (!curr->next)
				return (print_error(parsing_error, \
				curr->content->content), false);
			if (curr->next->content->type != file)
				return (print_error(parsing_error, \
				curr->next->content->content), false);
		}
		curr = curr->next;
	}
	return (true);
}

bool	check_all_consecutives_types(t_token_list *tokens)
{
	while (tokens && tokens->next)
	{
		if (((t_token *)tokens->content)->type != exec_name && \
			((t_token *)tokens->content)->type != arg && \
			((t_token *)tokens->content)->type != file)
		{
			if (((t_token *)tokens->next->content)->type != exec_name && \
				((t_token *)tokens->next->content)->type != arg && \
				((t_token *)tokens->next->content)->type != file)
			{
				if (((t_token *)tokens->content)->type == operator_pipe && \
					((t_token *)tokens->next->content)->type != operator_pipe)
				{
					tokens = tokens->next;
					continue ;
				}
				return (print_error(parsing_error, \
				tokens->next->content->content), false);
			}
		}
		tokens = tokens->next;
	}
	return (true);
}

bool	check_for_pipe_at_end(t_token_list *tokens)
{
	while (tokens && tokens->next)
	{
		tokens = tokens->next;
	}
	if (!tokens)
		return (true);
	if (tokens->content->type == operator_pipe)
		return (print_error(parsing_error, \
		tokens->content->content), false);
	return (true);
}

bool	check_redirect_operators(t_token *token)
{
	if (token->type == redirect_hd || token->type == redirect_out_append)
	{
		if (ft_strlen(token->content) > 2)
		{
			print_error(parsing_error, "");
			ft_putstr_fd("\'", 2);
			write(2, token->content + 2, 2);
			ft_putstr_fd("\'\n", 2);
			return (false);
		}
	}
	return (true);
}
