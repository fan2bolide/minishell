/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 00:00:00 by alevra            #+#    #+#             */
/*   Updated: 2023/02/13 00:00:00 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t ft_tabsize(void ** tab)
{
	size_t size;

	size = 0;
	if (tab == NULL)
		return (0);
	while (tab[size] != NULL)
		size++;
	return (size);
}

void **ft_dup_tab(void **tab, size_t sizeof_tab_elmnt)
{
	size_t tab_size;
	void	**tab_dup;
	size_t i;

	i = 0;
	if (!tab)
		return (ft_printf("%s : tab is null, returning null\n", __FUNCTION__ ),NULL);
	tab_size = ft_tabsize((void **)tab);
	tab_dup = malloc(tab_size * sizeof_tab_elmnt);
	if (!tab_dup)
		return (ft_printf("An error occurred (%s).\n", __FUNCTION__), NULL);
	while (i < tab_size)
	{
		tab_dup[i] = tab[i];
		i++;
	}
	return (tab_dup);
}