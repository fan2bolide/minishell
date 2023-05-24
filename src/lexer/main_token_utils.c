/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:43:37 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/12 06:16:11 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*allocate_token_content(char *expression, size_t i)
{
	char	*to_destroy;
	char	*content;

	content = ft_strnew(i);
	if (!content)
		return (NULL);
	to_destroy = ft_strncpy(expression, content, (int)i);
	content = ft_strtrim(to_destroy, " ");
	free(to_destroy);
	return (content);
}

char	*create_token_content(char *expression)
{
	size_t	i;

	i = 0;
	if (!ft_strchr(SPEC_CHAR, *expression) || *expression == '$')
	{
		while ((expression[i] && (!ft_strchr(SPEC_CHAR, expression[i]) || \
		expression[i] == '$' || ft_strchr("\"\'", expression[i])) && \
		!ft_isspace(expression[i])))
		{
			i += end_of_quote(expression + i);
			if (!expression[i++])
				return (NULL);
		}
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
	return (allocate_token_content(expression, i));
}

///
/// \param expression
/// \return the index of the end of the quote if <expression> is one
size_t	end_of_quote(char *expression)
{
	size_t	i;

	if (*expression != '\'' && *expression != '\"')
		return (0);
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
size_t	token_cmd_line_size(t_token_list *token_lst)
{
	size_t	res;

	if (!token_lst)
		return (1);
	if (token_lst->content->type != exec_name)
		return (0);
	res = count_strs(token_lst->content->content, ' ');
	token_lst = token_lst->next;
	while (token_lst && token_lst->content->type != operator_pipe)
	{
		if (token_lst->content->type == arg)
			res++;
		token_lst = token_lst->next;
	}
	return (res);
}
