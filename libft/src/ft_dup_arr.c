/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 00:00:00 by alevra            #+#    #+#             */
/*   Updated: 2023/04/12 06:09:16 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_arrsize(void **arr)
{
	size_t	size;

	size = 0;
	if (arr == NULL)
		return (0);
	while (arr[size] != NULL)
		size++;
	return (size);
}

void	cpy_arr(void **arr_src, void **arr_dest)
{
	size_t	i;

	i = 0;
	while (arr_src[i] && arr_dest[i] == NULL)
	{
		arr_dest[i] = arr_src[i];
		i++;
	}
	arr_src[i] = NULL;
	if (arr_src[i] != NULL)
	{
		ft_printf("%s error : tab_dest was not empty,", __FUNCTION__);
		ft_printf("couldn't copy entirely tab_src into tab_dest.\n");
	}
}

void	**ft_dup_arr(void **tab, size_t sizeof_tab_elemnt)
{
	size_t	tab_size;
	void	**tab_dup;

	if (!tab)
		return (ft_printf("%s : tab is null, returning null\n", __FUNCTION__),
			NULL);
	tab_size = ft_arrsize((void **)tab);
	tab_dup = ft_calloc((tab_size + 1), sizeof_tab_elemnt);
	if (!tab_dup)
		return (ft_printf("An error occurred (%s).\n", __FUNCTION__), NULL);
	cpy_arr(tab, tab_dup);
	return (tab_dup);
}
