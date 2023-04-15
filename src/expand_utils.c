/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 03:08:22 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/11 07:06:38 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expand_content.h"

void	remove_quotes(t_list *token_list)
{
	char	*tmp;

	while (token_list)
	{
		if (((t_expansion *)token_list->content)->type == quote)
		{
			tmp = ft_strtrim(((t_expansion *)token_list->content)->content, \
				"\'");
			free(((t_expansion *)token_list->content)->content);
			((t_expansion *)token_list->content)->content = tmp;
		}
		if (((t_expansion *)token_list->content)->type == double_quote)
		{
			tmp = ft_strtrim(((t_expansion *)token_list->content)->content, \
				"\"");
			free(((t_expansion *)token_list->content)->content);
			((t_expansion *)token_list->content)->content = tmp;
		}
		token_list = token_list->next;
	}
}

char	*join_contents(t_list *token_list)
{
	char		*res;
	char		*to_destroy;
	t_expansion	*token;

	res = NULL;
	to_destroy = ft_calloc(1, 1);
	while (token_list)
	{
		token = token_list->content;
		res = ft_strjoin(to_destroy, token->content);
		free(to_destroy);
		to_destroy = res;
		token_list = token_list->next;
	}
	return (res);
}
