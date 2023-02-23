/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 00:03:34 by bajeanno          #+#    #+#             */
/*   Updated: 2022/11/10 22:56:27 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*source;

	source = (unsigned char *)src;
	dest = (unsigned char *)dst;
	i = 0;
	while (i < n && source[i] != (unsigned char)c)
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
