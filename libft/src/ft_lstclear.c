/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:45:28 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/23 03:40:25 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*delete;

	if (!lst)
		return ;
	delete = *lst;
	while (delete)
	{
		curr = delete->next;
		del(delete->content);
		free(delete);
		delete = curr;
	}
	*lst = NULL;
}

void	ft_lstclear_mais_pas_trop(t_list **lst)
{
	t_list	*curr;
	t_list	*delete;

	if (!lst)
		return ;
	delete = *lst;
	while (delete)
	{
		curr = delete->next;
		free(delete);
		delete = curr;
	}
	*lst = NULL;
}
