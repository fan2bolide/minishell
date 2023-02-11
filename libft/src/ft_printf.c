/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:42:41 by bajeanno          #+#    #+#             */
/*   Updated: 2022/12/08 00:16:39 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_value(char c, va_list *values, size_t *i)
{
	if (c == 0)
		return (*i = *i - 1, 0);
	if (c == 'p')
		return (ft_print_addr(va_arg(*values, void *)));
	if (c == 'd' || c == 'i')
		return (ft_print_int(va_arg(*values, int)));
	if (c == 'x')
		return (ft_print_hexa(va_arg(*values, int)));
	if (c == 'X')
		return (ft_print_hexa_capslock(va_arg(*values, int)));
	if (c == 'u')
		return (ft_print_unsigned(va_arg(*values, unsigned int)));
	if (c == '%')
		return (write(1, "%", 1));
	if (c == 's')
		return (ft_putstr(va_arg(*values, char *)));
	if (c == 'c')
		return (ft_putchar(va_arg(*values, int)));
	return (0);
}

static int	ft_printf2(const char *format, va_list *values)
{
	size_t	i;
	size_t	size;
	int		error;

	size = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			error = ft_print_value(format[++i], values, &i);
			if (error < 0)
				return (error);
			size += error;
		}
		else
		{
			error = write(1, format + i, 1);
			if (error < 0)
				return (error);
			size += error;
		}
		i++;
	}
	return (size);
}

int	ft_printf(const char *format, ...)
{
	va_list	values;
	int		res;

	if (!format)
		return (0);
	va_start(values, format);
	res = ft_printf2(format, &values);
	va_end(values);
	return (res);
}
