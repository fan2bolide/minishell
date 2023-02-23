/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 09:25:14 by bajeanno          #+#    #+#             */
/*   Updated: 2022/12/06 19:42:53 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_addr(void *ptr)
{
	int	result;

	result = write(1, "0x", 2);
	if (result != 2)
		return (-1);
	return (ft_putnbr_base_unsigned((size_t)ptr, "0123456789abcdef") + result);
}

int	ft_print_hexa(int nb)
{
	return (ft_putnbr_base_unsigned((unsigned int)nb, "0123456789abcdef"));
}

int	ft_print_hexa_capslock(int nb)
{
	return (ft_putnbr_base_unsigned((unsigned int)nb, "0123456789ABCDEF"));
}
