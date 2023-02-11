/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:40:24 by bajeanno          #+#    #+#             */
/*   Updated: 2022/11/19 06:58:11 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len;

	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	res = ft_strnew(len);
	if (res == NULL)
		return (NULL);
	*res = 0;
	ft_strcat(res, (char *)s1);
	ft_strcat(res, (char *)s2);
	return (res);
}
