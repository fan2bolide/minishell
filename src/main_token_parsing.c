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

static bool	number_of_pipes_is_above_limit(t_token_list *tokenized_pipeline)
{
	size_t	i;

	i = 0;
	while (tokenized_pipeline && i < (OPEN_MAX - 3) / 2)
	{
		if (tokenized_pipeline->content->type == operator_pipe)
			i++;
		tokenized_pipeline = tokenized_pipeline->next;
	}
	if (!tokenized_pipeline)
		return (false);
	return (print_error(parsing_error, \
		tokenized_pipeline->content->content), true);
}

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
	!check_files_after_redirect(tokens) || !check_for_pipe_at_end(tokens) || \
	number_of_pipes_is_above_limit(tokens))
		return (ft_lstclear((t_list **)&tokens, destroy_token), NULL);
	return (tokens);
}
