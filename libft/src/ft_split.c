/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 02:07:40 by bajeanno          #+#    #+#             */
/*   Updated: 2023/02/23 15:13:32 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_strs(const char *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			return (count);
		while (s[i] && s[i] != c)
			i++;
		count++;
	}
	return (count);
}

static size_t	ft_strclen(const char *s, char c)
{
	size_t	i;
	size_t	count;

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

static char	*get_string(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	while (s[i] && s[i] == c)
		i++;
	return (s + i);
}

static void	ft_add_strings(char **strs, char c, char *newstr, size_t count)
{
	size_t	i;

	i = 1;
	while (i < count)
	{
		strs[i] = get_string(strs[i - 1], c);
		if (!strs[i])
			return (free(newstr), free(strs), (void)0);
		strs[i - 1][ft_strclen(strs[i - 1], c)] = 0;
		i++;
	}
	strs[i] = NULL;
}

char	**ft_split(const char *s, char c)
{
	char	**strs;
	char	*newstr;
	char	sep[2];
	size_t	count;

	count = count_strs(s, c);
	strs = malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);
	sep[0] = c;
	sep[1] = 0;
	newstr = ft_strtrim(s, sep);
	if (!newstr)
		return (free(strs), NULL);
	strs[0] = newstr;
	ft_add_strings(strs, c, newstr, count);
	return (strs);
}
