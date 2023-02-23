/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 01:03:01 by bajeanno          #+#    #+#             */
/*   Updated: 2022/11/10 13:42:42 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_get_count(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	assign_value(int n, size_t len, char *ptr)
{
	size_t	i;

	i = len - 1;
	while (n > 0)
	{
		ptr[i--] = n % 10 + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	size_t			len;
	char			*ptr;
	int				minus;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = ft_itoa_get_count(n);
	minus = 0;
	if (n < 0)
	{
		len++;
		minus++;
		n = -n;
	}
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	assign_value(n, len, ptr);
	ptr[len] = 0;
	if (minus)
		*ptr = '-';
	return (ptr);
}
