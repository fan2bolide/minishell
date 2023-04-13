/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 06:05:28 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/12 06:07:44 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_lst_to_arr(t_list *lst, size_t size_of_arr_elemnt)
{
	size_t	arr_size;
	void	**arr;
	int		i;

	arr_size = ft_lstsize(lst);
	arr = ft_calloc(arr_size + 1, size_of_arr_elemnt);
	i = 0;
	while (lst)
	{
		arr[i++] = lst->content;
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}
