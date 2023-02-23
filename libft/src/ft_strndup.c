/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:41:21 by bajeanno          #+#    #+#             */
/*   Updated: 2022/11/19 06:28:15 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, size_t n)
{
	char	*newstr;

	if (n > ft_strlen(str))
		n = ft_strlen(str);
	newstr = ft_strnew(n);
	if (!newstr)
		return (NULL);
	ft_strncat(newstr, str, n);
	return (newstr);
}
