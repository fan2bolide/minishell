/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 02:51:45 by bajeanno          #+#    #+#             */
/*   Updated: 2022/11/05 02:51:46 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	total_size;
	size_t	i;
	size_t	j;

	total_size = ft_strlen(src) + ft_strlen(dst);
	if (dstsize <= (size_t)ft_strlen(dst))
		return (ft_strlen(src) + dstsize);
	j = 0;
	i = 0;
	while (dst[i] && i < dstsize - 1)
		i++;
	while (src[j] && i < dstsize - 1)
		dst[i++] = src[j++];
	dst[i] = 0;
	return (total_size);
}
