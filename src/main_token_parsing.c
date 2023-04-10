/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <ba...@student.42lyon.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:06:38 by bajeanno          #+#    #+#             */
/*   Updated: 2023/03/07 11:01:37 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	check_all_consecutives_types(t_token_list *tokens);
static int	check_files_after_redirect(t_token_list *tokens);
static bool	check_for_pipe_at_end(t_token_list *tokens);
static bool check_redirect_operators(t_token *token);
/*
 * checks for parsing rules
 * RULE 1 : there can't be two consecutive redirect operator V
 *
 * RULE 2 : There can't be two consecutive pipes (we do not handle minishell
 * bonuses..) V
 *
 * RULE 3 : after a redirect comes automatically a file Veneral Vegaulle
 *
 * RULE 4 : after a file comes either :
 * 			- an exec_name (ex : "< file cat " )
 * 			- a redirect operator (ex : "< file > file2 < file3 > file4 cat ")
 * 			- a pipe operator (ex : "cat < file | cat" )
 *
 * 	----------------------------jusqu'a preuve du contraire c'est bon.
 * todo : search for other rules to be applicated.
 */
t_token_list	*token_parsing(t_token_list *tokens)
{
	t_token_list	*curr;

	curr = tokens;
	if (curr->content->type == operator_pipe)
		return (print_error(parsing_error, curr->content->content), \
					ft_lstclear((t_list **)&tokens, destroy_token), NULL);
	while (curr)
	{
		if (curr->content->type == error)
			return (print_error(parsing_error, curr->content->content), \
					ft_lstclear((t_list **)&tokens, destroy_token), NULL);
		if (!check_redirect_operators(curr->content))
			return (ft_lstclear((t_list **)&tokens, destroy_token), NULL);
		curr = curr->next;
	}
	curr = tokens;
	if (!check_all_consecutives_types(tokens) || \
	curr->content->type == operator_pipe || \
	!check_files_after_redirect(tokens) || !check_for_pipe_at_end(tokens))
		return (ft_lstclear((t_list **)&tokens, destroy_token), NULL);
	return (tokens);
}

int	check_files_after_redirect(t_token_list *tokens)
{
	t_token_list *curr;

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
				curr->content->content), 0);
			if (curr->next->content->type != file)
				return (print_error(parsing_error, \
				curr->next->content->content), 0);
		}
		curr = curr->next;
	}
	return (1);
}

int	check_all_consecutives_types(t_token_list *tokens)
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
					continue;
				}
				return (print_error(parsing_error, \
				tokens->next->content->content), 0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
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

static bool check_redirect_operators(t_token *token)
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
