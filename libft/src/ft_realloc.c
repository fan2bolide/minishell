/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 00:57:26 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/20 01:03:01 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *data, size_t size, size_t new_size)
{
	void	*new_data;

	new_data = malloc(new_size);
	if (!new_data)
		return (write(2, "Error\n", 6), NULL);
	ft_memmove(new_data, data, size);
	free(data);
	return (new_data);
}
