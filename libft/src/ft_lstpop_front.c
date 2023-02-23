/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 04:54:40 by bajeanno          #+#    #+#             */
/*   Updated: 2022/12/15 22:29:40 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpop_front(t_list **list, void (*del)(void *))
{
	t_list	*remove;

	remove = *list;
	*list = (*list)->next;
	ft_lstdelone(remove, del);
}
