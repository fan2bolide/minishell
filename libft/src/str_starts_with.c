/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_starts_with.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 06:01:00 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/12 06:01:02 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 *
 * @param str
 * @param keyword
 * @return 1 if str starts with keyword, 0 if not
 */
int	str_starts_with(char *str, char *keyword)
{
	return (!ft_strncmp(str, keyword, ft_strlen(keyword)));
}
