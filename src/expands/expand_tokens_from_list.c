/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_from_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 08:08:45 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/11 07:05:45 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expand_content.h"

int	expand_tokens_from_list(t_token_list *token_list)
{
	t_token	*token;

	while (token_list)
	{
		token = token_list->content;
		if (token->type == redirect_hd)
			token_list = token_list->next;
		else
		{
			token->content = expand_content(token->content);
			if (!token->content)
				return (ft_lstclear((t_list **)&token_list, destroy_token), 0);
		}
		token_list = token_list->next;
	}
	return (1);
}
