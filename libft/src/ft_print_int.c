/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:26:53 by bajeanno          #+#    #+#             */
/*   Updated: 2022/12/08 00:16:24 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_int(int nb)
{
	return (ft_putnbr(nb));
}

int	ft_print_unsigned(unsigned int nb)
{
	int	res;
	int	error;

	res = 0;
	error = 0;
	if (nb >= 10)
		error = ft_print_unsigned(nb / 10);
	if (error < 0)
		return (error);
	res += error;
	error = ft_putchar(nb % 10 + '0');
	if (error < 0)
		return (error);
	res += error;
	return (res);
}
