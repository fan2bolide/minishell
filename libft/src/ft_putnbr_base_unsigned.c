/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:07:25 by bajeanno          #+#    #+#             */
/*   Updated: 2022/12/06 22:11:29 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_verif_base(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i + 1])
	{
		j = i + 1;
		while (str[j])
		{
			if (str[i] == str[j])
				return (0);
			j++;
		}
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			return (0);
		i++;
	}
	return (1);
}

int	ft_putnbr_base_unsigned(size_t nbr, char *base)
{
	size_t	base_length;
	size_t	res;
	int		sign;
	int		error;

	res = 0;
	sign = 1;
	base_length = ft_strlen(base);
	if (!ft_verif_base(base) || base_length < 2)
		return (0);
	if (nbr >= base_length)
	{
		error = ft_putnbr_base_unsigned(nbr / base_length * sign, base);
		if (error < 0)
			return (error);
		res += error;
	}
	error = write(1, &base[nbr % base_length * sign], 1);
	if (error < 0)
		return (error);
	return (res + error);
}
