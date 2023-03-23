/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 03:08:22 by bajeanno          #+#    #+#             */
/*   Updated: 2023/03/23 00:12:45 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_token.h"

void	remove_quotes(t_list *token_list)
{
	while (token_list)
	{
		if (((t_expansion *)token_list->content)->type == quote)
			((t_expansion *)token_list->content)->content = \
			ft_strtrim(((t_expansion *)token_list->content)->content, "\'");
		if (((t_expansion *)token_list->content)->type == double_quote)
			((t_expansion *)token_list->content)->content = \
			ft_strtrim(((t_expansion *)token_list->content)->content, "\"");
		token_list = token_list->next;
	}
}

char	*join_contents(t_list *token_list)
{
	char	*res;
	char	*to_destroy;

	to_destroy = ft_calloc(1, 1);
	while (token_list)
	{
		res = ft_strjoin(to_destroy, \
		((t_expansion *)token_list->content)->content);
		to_destroy = res;
		token_list = token_list->next;
	}
	return (res);
}

char	*get_value_of_var(char *var, t_str_list **envp)
{
	char	*value;
	char	*var_name;
	int		i;

	i = 0;
	while (var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	var_name = ft_strnew(i);
	var_name = ft_strncpy(var, var_name, i);
	value = get_env_var(var_name, envp);
	free(var_name);
	return (value);
}

static char	*join_words_with_values(t_expansion *token, size_t i, char *tmp, \
								t_str_list **envp)
{
	char	*value;

	while (token->content[i])
	{
		token->content += i;
		i = 0;
		while (token->content[i] && token->content[i] != '$')
			i++;
		tmp = ft_strnjoin(tmp, token->content, (int)i++);
		value = get_value_of_var(token->content + i, envp);
		if (!value)
			value = "";
		tmp = ft_strjoin(tmp, value);
		while (token->content[i] && (ft_isalnum(token->content[i]) || \
				token->content[i] == '_'))
			i++;
	}
	return (tmp);
}

int	replace_with_value(void *expansion_token, t_str_list **envp)
{
	t_expansion	*token;
	char		*token_content_save;
	size_t		i;
	char		*tmp;

	token = expansion_token;
	if (token->type != quote)
	{
		if (!ft_strchr(token->content, '$'))
			return (1);
		tmp = ft_strnew(0);
		if (!tmp)
			return (0);
		token_content_save = token->content;
		i = 0;
		tmp = join_words_with_values(token, i, tmp, envp);
		free(token_content_save);
		token->content = tmp;
	}
	return (1);
}
