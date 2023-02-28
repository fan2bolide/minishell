/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:43:40 by bajeanno          #+#    #+#             */
/*   Updated: 2023/02/27 21:44:16 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	destroy_token(void *token);

char	*get_token_content(char *expression)
{
	size_t	i;
	char	*content;

	i = 0;
	if (ft_isalnum(*expression) || *expression == '-')
		while (expression[i] && (ft_isalnum(expression[i]) || \
		expression[i] == '-'))
			i++;
	else
		if (ft_strchr(SPEC_CHAR, *expression))
			while (expression[i] && *expression == expression[i])
				i++;
		else
			return (NULL);
	content = ft_strnew(i);
	if (!content)
		return (NULL);
	ft_strncpy(expression, content, (int)i);
	return (content);
}

void	destroy_token_list(t_list *token_list)
{
	ft_lstclear(&token_list, destroy_token);
}

static void	destroy_token(void *token)
{
	free(((t_token *)token)->content);
	free(token);
}