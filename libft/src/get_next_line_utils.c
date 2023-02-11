/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:38:45 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/20 00:56:37 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*ft_realloc_str(char *str, int new_size)
{
	char	*newstr;
	size_t	len_str;

	if (str == NULL)
		return (NULL);
	newstr = malloc(sizeof(char) * new_size);
	if (newstr == NULL)
		return (NULL);
	len_str = 0;
	while (str[len_str])
		len_str++;
	ft_memmove(newstr, str, len_str + 1);
	free(str);
	return (newstr);
}

char	*ft_strfusion(char const *buf, int *size, char *line, int buf_size)
{
	if (buf_size == 0)
		return (line);
	*size += buf_size;
	line = ft_realloc_str(line, *size);
	line = ft_strncat(line, buf, buf_size);
	return (line);
}
