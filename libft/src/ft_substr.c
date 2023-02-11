/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:41:05 by bajeanno          #+#    #+#             */
/*   Updated: 2022/11/19 06:28:33 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	if (start < ft_strlen(s))
	{
		if (len > 0)
			return (ft_strndup((char *)s + start, len));
		return (ft_calloc(1, 1));
	}
	return (ft_calloc(1, 1));
}
