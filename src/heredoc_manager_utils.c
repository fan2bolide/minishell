/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:25:43 by alevra            #+#    #+#             */
/*   Updated: 2023/02/08 22:12:59 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	cpy_except_quotes(const char *raw, int i, char *res, int *j);

int	append_str(char **str_to_append, char *next_line)
{
	char	*str_to_append_tmp;

	if (!*str_to_append)
	{
		*str_to_append = ft_strdup(next_line);
		return (1);
	}
	str_to_append_tmp = ft_strjoin(*str_to_append, next_line);
	free(*str_to_append);
	*str_to_append = str_to_append_tmp;
	if (!str_to_append_tmp)
		return (print_error(alloc_error, "(here_doc)(append_line)"), 0);
	return (1);
}

char	*remove_quotes_heredoc(const char *raw)
{
	int		res_size;
	int		i;
	char	*res;
	int		j;

	res_size = 0;
	i = 0;
	if (!raw)
		return (NULL);
	while (raw[i])
	{
		res_size += ((raw[i] != '\'') && (raw[i] != '\"'));
		i++;
	}
	res = ft_calloc(res_size +1, sizeof(char));
	if (!res)
	{
		print_error(alloc_error, "(remove quotes)");
		return (NULL);
	}
	cpy_except_quotes(raw, i, res, &j);
	res[j] = 0;
	return (res);
}

static void	cpy_except_quotes(const char *raw, int i, char *res, int *j)
{
	i = 0;
	*j = 0;
	while (raw[i])
	{
		if ((raw[i] != '\'') && (raw[i] != '\"'))
		{
			res[*j] = raw[i];
			(*j)++;
		}
		i++;
	}
}
