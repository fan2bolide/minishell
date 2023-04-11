/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 03:08:22 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/11 07:06:38 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expand_content.h"

void	remove_quotes(t_list *token_list)
{
	char	*tmp;

	while (token_list)
	{
		if (((t_expansion *)token_list->content)->type == quote)
		{
			tmp = ft_strtrim(((t_expansion *)token_list->content)->content, \
				"\'");
			free(((t_expansion *)token_list->content)->content);
			((t_expansion *)token_list->content)->content = tmp;
		}
		if (((t_expansion *)token_list->content)->type == double_quote)
		{
			tmp = ft_strtrim(((t_expansion *)token_list->content)->content, \
				"\"");
			free(((t_expansion *)token_list->content)->content);
			((t_expansion *)token_list->content)->content = tmp;
		}
		token_list = token_list->next;
	}
}

char	*join_contents(t_list *token_list)
{
	char		*res;
	char		*to_destroy;
	t_expansion	*token;

	res = NULL;
	to_destroy = ft_calloc(1, 1);
	while (token_list)
	{
		token = token_list->content;
		res = ft_strjoin(to_destroy, token->content);
		free(to_destroy);
		to_destroy = res;
		token_list = token_list->next;
	}
	return (res);
}

char	*get_value_of_var(char *var)
{
	char	*value;
	char	*var_name;
	int		i;

	i = 0;
	if (var[0] == '?')
		i = 1;
	else
		while (var[i] && var[i] != '?' && (ft_isalnum(var[i]) || var[i] == '_'))
			i++;
	if (i == 0)
		return (NULL);
	var_name = ft_strnew(i);
	var_name = ft_strncpy(var, var_name, i);
	value = get_env_var_value(var_name);
	free(var_name);
	return (value);
}

static char	*join_words_with_values(t_expansion *token, char *tmp)
{
	char	*value;
	char	*to_destroy;
	size_t	i;

	i = 0;
	while (token->content[i])
	{
		token->content += i;
		i = 0;
		while (token->content[i] && token->content[i] != '$')
			i++;
		to_destroy = tmp;
		tmp = ft_strnjoin(to_destroy, token->content, (int)i);
		free(to_destroy);
		if (!token->content[i])
			return (tmp);
		i++;
		value = get_value_of_var(token->content + i);
		if (!value)
			value = "";
		to_destroy = tmp;
		tmp = ft_strjoin(tmp, value);
		free(to_destroy);
		while (token->content[i] && token->content[i] != '?' && \
				(ft_isalnum(token->content[i]) || token->content[i] == '_'))
			i++;
		if (token->content[i] == '?')
			i++;
	}
	return (tmp);
}

int	replace_with_value(void *expansion_token)
{
	t_expansion	*token;
	char		*tmp;

	token = expansion_token;
	if (token->type != quote)
	{
		if (!ft_strchr(token->content, '$'))
			return (1);
		tmp = ft_strnew(0);
		if (!tmp)
			return (0); //todo error message here
		tmp = join_words_with_values(token, tmp);
		free(token->content);
		token->content = tmp;
	}
	return (1);
}
