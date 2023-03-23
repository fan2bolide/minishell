/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 08:08:45 by bajeanno          #+#    #+#             */
/*   Updated: 2023/03/23 08:08:51 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_content.h"

int	expand_tokens_from_list(t_list *token_list, t_str_list *envp)
{
	t_list *curr;
	t_token *token;

	curr = token_list;
	while (curr)
	{
		token = curr->content;
		if (token->type == redirect_hd)
			curr = curr->next;
		else
		{
			token->content = expand_content(token->content, &envp);
			if (!token->content)
				return (ft_lstclear(&token_list, destroy_token), 0);
		}
		curr = curr->next;
	}
	return (1);
}