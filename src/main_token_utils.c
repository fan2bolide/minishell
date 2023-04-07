/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <ba...@student.42lyon.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:43:37 by bajeanno          #+#    #+#             */
/*   Updated: 2023/03/06 14:59:22 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*set_token_content(char *expression)
{
	size_t	i;
	char	*content;
	char	*to_destroy;

	i = 0;
	if (!ft_strchr(SPEC_CHAR, *expression) || *expression == '$')
		while ((expression[i] && (!ft_strchr(SPEC_CHAR, expression[i]) || \
		expression[i] == '$' || ft_strchr("\"\'", expression[i])) &&
		!ft_isspace(expression[i])))
		{
			if (ft_strchr("\"\'", expression[i]))
				i += end_of_quote(expression + i);
			if (!expression[i])
				return (NULL);
			i++;
		}
	else
	{
		while (expression[i] && *expression == expression[i])
			i++;
		if (*expression == '$' && i == 1)
			while (expression[i] && \
			!ft_strchr(SPEC_CHAR, expression[i]) && \
			!ft_isspace(expression[i]))
				i++;
	}
	content = ft_strnew(i);
	if (!content)
		return (NULL);
	to_destroy = ft_strncpy(expression, content, (int)i);
	content = ft_strtrim(to_destroy, " ");
	free(to_destroy);
	return (content);
}

/*
 * in absolute, it will search for the next occurrence of the first char in
 * the string. But if you send it a quote, it will bring you the index of the
 * end of the quote.
 */
size_t	end_of_quote(char *expression)
{
	size_t	i;

	i = 1;
	while (expression[i] && expression[i] != *expression)
		i++;
	return (i);
}

void	destroy_token(void *token)
{
	free(((t_token *)token)->content);
	free(token);
}

// for a exec_name line (given into a token-list format),
// returns 1(for the exec_name) + the number of args following the exec_name
//ex : "echo te quiero loco | ... ": returns 4
//ex : "ls | ..." : returns only 1
//ex : "< file | ..." : returns 0
size_t token_cmd_line_size(t_token_list *token_lst)
{
	size_t	res;

	if (!token_lst)
		return 1;
	if (token_lst->content->type != exec_name)
		return (0);
	res = count_strs(token_lst->content->content, ' ');
	token_lst = token_lst->next;
	while (token_lst && token_lst->content->type == arg)
	{
		res++;
		token_lst = token_lst->next;
	}
	return (res);
}

bool	number_of_pipes_is_above_limit(t_list *tokenized_pipeline)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (tokenized_pipeline && i < (FOPEN_MAX - 3) / 2)
	{
		token = tokenized_pipeline->content;
		if (token->type == operator_pipe)
			i++;
		tokenized_pipeline = tokenized_pipeline->next;
	}
	if (!tokenized_pipeline)
		return (false);
	return (print_error(parsing_error, token->content), true);
}

//static int token_is_null(void *token_lst_content)
//{
//	t_token *token;
//
//	token = token_lst_content;
//	return (token->content == NULL);
//}
