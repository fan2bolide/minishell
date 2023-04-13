/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_old_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 02:49:33 by bajeanno          #+#    #+#             */
/*   Updated: 2022/12/08 04:34:27 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strclen(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		i++;
		count++;
	}
	return (count);
}

static char	*get_string(char *return_str, const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
		return_str[j++] = s[i++];
	return_str[j] = 0;
	return (return_str);
}

static void	ft_free_all(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**ft_old_split(const char *s, char c)
{
	char	**strs;
	int		count;
	int		i;

	i = 0;
	count = count_strs(s, c);
	strs = malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);
	while (i < count)
	{
		strs[i] = ft_strnew(ft_strclen(s, c));
		if (!strs[i])
			return (ft_free_all(strs), NULL);
		get_string(strs[i], s, c);
		s += ft_strclen(s, c) - 1;
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
			s++;
		i++;
	}
	return (strs[i] = NULL, strs);
}
