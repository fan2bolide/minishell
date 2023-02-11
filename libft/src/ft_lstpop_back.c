/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 05:04:01 by bajeanno          #+#    #+#             */
/*   Updated: 2022/12/15 22:30:31 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpop_back(t_list **list, void (*del)(void *))
{
	t_list	*first;

	first = *list;
	*list = (*list)->next;
	ft_lstdelone(first, del);
}
