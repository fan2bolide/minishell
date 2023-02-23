/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:02:04 by bajeanno          #+#    #+#             */
/*   Updated: 2022/12/14 05:12:54 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int nb)
{
	size_t	res;
	int		error;

	res = 0;
	error = 0;
	if (nb == INT_MIN)
		return (ft_putstr("-2147483648"));
	if (nb < 0)
	{
		error = ft_putchar('-');
		if (error < 0)
			return (error);
		res++;
		nb = -nb;
	}
	error = 0;
	if (nb >= 10)
		error = ft_putnbr(nb / 10);
	if (error < 0)
		return (error);
	res += error;
	error = ft_putchar(nb % 10 + '0');
	if (error < 0)
		return (error);
	return (res + error);
}
