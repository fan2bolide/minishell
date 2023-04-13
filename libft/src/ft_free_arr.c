/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 06:11:04 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/12 06:11:43 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//last element of array must be a NULL pointer
void	ft_free_arr(void **array, void (*del)(void *))
{
	int	i;

	i = 0;
	while (array[i])
		del(array[i++]);
}
