/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_with_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:40:01 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/15 18:40:02 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expand_content.h"

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
		return (ft_strdup("$"));
	var_name = ft_strnew(i);
	var_name = ft_strncpy(var, var_name, i);
	value = get_env_var_value(var_name);
	free(var_name);
	return (value);
}

static char	*add_var(const t_expansion *token, size_t i, char *content)
{
	char	*value;

	value = get_value_of_var(token->content + i);
	if (!value)
		value = "";
	content = ft_strjoin_free_s1(content, value);
	if (*value == '$')
		free(value);
	return (content);
}

static char	*join_words_with_values(t_expansion *token, char *tmp)
{
	size_t	i;

	i = 0;
	while (token->content[i])
	{
		token->content += i;
		i = 0;
		while (token->content[i] && token->content[i] != '$')
			i++;
		tmp = ft_strnjoin_free_s1(tmp, token->content, (int)i);
		if (!token->content[i])
			return (tmp);
		i++;
		tmp = add_var(token, i, tmp);
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
	char		*content_save;

	token = expansion_token;
	content_save = token->content;
	if (token->type != quote)
	{
		if (!ft_strchr(token->content, '$'))
			return (1);
		tmp = ft_strnew(0);
		if (!tmp)
			return (print_error(alloc_error, "replace_with_value"), 0);
		tmp = join_words_with_values(token, tmp);
		free(content_save);
		token->content = tmp;
	}
	return (1);
}
