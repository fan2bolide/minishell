/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_be_converted_to_long.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 06:03:13 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/12 06:04:46 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define UPPER_STR_LENGTH_LIMIT_FOR_A_LONG 21
#define LOWER_STR_LENGTH_LIMIT_FOR_A_LONG 19

bool	can_be_converted_to_long(char *argv1)
{
	size_t				argv1_len;
	long long			atoll_res;

	argv1_len = ft_strlen(argv1);
	if (argv1_len > UPPER_STR_LENGTH_LIMIT_FOR_A_LONG)
		return (false);
	if (argv1_len < LOWER_STR_LENGTH_LIMIT_FOR_A_LONG)
		return (true);
	atoll_res = ft_atoll(argv1);
	if (atoll_res == 0 || atoll_res == -1)
		return (false);
	return (true);
}
