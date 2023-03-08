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

/*
 * checks for parsing rules
 * RULE 1 : there can't be two consecutive redirect operator
 * RULE 2 : a command cannot begin with a pipe (but it can begin with a
 * redirect operator)
 * RULE 3 : There can't be two consecutive pipes (we do not handle minishell
 * bonuses..)
 * RULE 4 : an exec MUST NOT start with a hyphen '-'
 * RULE 5 : an arg MUST start with a hyphen '-'
 * RULE 6 : there can't be two exec_name in the same command
 * RULE 7 : after a redirect comes automatically a file
 * RULE 8 : after a file comes either :
 * 			- an exec_name (ex : "< file cat " )
 * 			- a redirect operator (ex : "< file > file2 cat " )
 * 			- a pipe operator (ex : "cat < file | cat" )
 * RULE 9 : before an arg, comes an arg or exec_name. Nothing else is allowed
 * todo : search for other rules to be applicated.
 */
t_list	*token_parsing(t_list *tokens)
{
	t_list	*curr;
	t_token *curr_token;

	curr = tokens;
	while (curr)
	{
		curr_token = curr->content;
		if (curr_token->type == error)
			return (ft_lstclear(&tokens, free), NULL);
		if (curr_token->type != exec_name && curr_token->type != arg &&\
			curr_token->type != file)
		{
			curr_token = curr->next->content;
			if (curr_token->type != exec_name && curr_token->type != arg &&\
			curr_token->type != file)
				return (ft_lstclear(&tokens, free), NULL);
		}
	}
	return (tokens);
}

static int	check_consecutives_types(t_list *list, t_type type1, t_type type2)
{
	while (list && list->next)
	{
		if (((t_token *)list->content)->type == type1 && \
		((t_token *)list->next->content)->type == type2)
			return (0);
		list = list->next;
	}
	return (1);
}
