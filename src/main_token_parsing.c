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

static int	check_all_consecutives_types(t_list *tokens);
static int	check_files_after_redirect(t_list *tokens);

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
t_list	*token_parsing(t_list *tokens)
{
	t_list	*curr;
	t_token *curr_token;

	curr = tokens;
	if (!check_all_consecutives_types(tokens) || \
	((t_token *)tokens->content)->type == operator_pipe || \
	!check_files_after_redirect(tokens))
		return (ft_lstclear(&tokens, destroy_token), NULL);
	while (curr)
	{
		curr_token = curr->content;
		if (curr_token->type == error)
			return (ft_lstclear(&tokens, destroy_token), NULL);
		curr = curr->next;
	}
	return (tokens);
}

int	check_files_after_redirect(t_list *tokens)
{
	t_list *curr;

	curr = tokens;
	while (curr)
	{
		if (((t_token *)curr->content)->type == redirect_in || \
			((t_token *)curr->content)->type == redirect_out_trunc || \
			((t_token *)curr->content)->type == redirect_out_append || \
			((t_token *)curr->content)->type == redirect_hd)
			if (!curr->next || ((t_token *)curr->next->content)->type != file)
				return (0);
		curr = curr->next;
	}
	return (1);
}

int	check_all_consecutives_types(t_list *tokens)
{
	t_list	*curr;

	curr = tokens;
	while (curr && curr->next)
	{
		if (((t_token *)curr->content)->type != exec_name && \
			((t_token *)curr->content)->type != arg && \
			((t_token *)curr->content)->type != file)
		{
			if (((t_token *)curr->next->content)->type != exec_name && \
				((t_token *)curr->next->content)->type != arg && \
				((t_token *)curr->next->content)->type != file)
			{
				if (((t_token *)curr->content)->type == operator_pipe && \
					((t_token *)curr->next->content)->type != operator_pipe)
				{
					curr = curr->next;
					continue;
				}
				return (0);
			}
		}
		curr = curr->next;
	}
	return (1);
}
