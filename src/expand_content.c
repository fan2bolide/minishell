/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 03:08:22 by bajeanno          #+#    #+#             */
/*   Updated: 2023/03/23 08:06:58 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand_content.h"

static char	*get_clean_content(char *raw_content)
{
	char	*clean_content;
	size_t	i;

	i = 0;
	if (*raw_content == '\'')
	{
		i++;
		while (raw_content[i] && raw_content[i] != '\'')
			i++;
		i++;
	}
	else
	{
		if (*raw_content == '\"')
		{
			i++;
			while (raw_content[i] && raw_content[i] != '\"')
				i++;
			i++;
		}
		else
			while (raw_content[i] && !ft_strchr("\'\"", raw_content[i]))
				i++;
	}
	clean_content = ft_strnew(i);
	if (!clean_content)
		return (NULL);
	return (ft_strncpy(raw_content, clean_content, (int)i));
}

static t_expansion	*evaluate_token(char *raw_content)
{
	t_expansion	*token;

	token = ft_calloc(1, sizeof (t_expansion));
	if (!token)
		return (NULL);
	if (*raw_content == '\'')
		return (token->type = quote, \
			token->content = get_clean_content(raw_content), token);
	if (*raw_content == '\"')
		return (token->type = double_quote, \
			token->content = get_clean_content(raw_content), token);
	return (token->type = word, \
		token->content = get_clean_content(raw_content), token);
}

static size_t	get_next_token(char *token_content)
{
	size_t	i;

	i = 0;
	if (*token_content == '\'')
	{
		i++;
		while (token_content[i] && token_content[i] != '\'')
			i++;
		return (i + 1);
	}
	if (*token_content == '\"')
	{
		i++;
		while (token_content[i] && token_content[i] != '\"')
			i++;
		return (i + 1);
	}
	while (token_content[i] && !ft_strchr("\'\"", token_content[i]))
		i++;
	return (i);
}

static t_list	*get_expand_token_list(char *raw_content)
{
	t_list	*list;
	t_list	*curr;
	size_t	i;

	i = 0;
	if (!raw_content || !*raw_content)
		return (NULL);
	list = ft_lstnew(evaluate_token(raw_content));
	curr = list;
	if (!curr)
		return (ft_lstclear(&list, destroy_expand_token), NULL);
	curr->next = (NULL);
	i = get_next_token(raw_content);
	while (raw_content[i])
	{

		curr->next = ft_lstnew(evaluate_token(raw_content + i));
		curr = curr->next;
		if (!curr)
			return (ft_lstclear(&list, destroy_expand_token), NULL);
		i += get_next_token(raw_content + i);
	}
	return (list);
}

char *expand_content(char *raw_content)
{
	t_list	*list = get_expand_token_list(raw_content);
	t_list	*curr;

	remove_quotes(list);
	curr = list;
	while (curr)
	{
		if (!replace_with_value(curr->content))
			return (ft_lstclear(&list, destroy_expand_token), NULL);
		curr = curr->next;
	}
	free(raw_content);
	raw_content = join_contents(list);
	ft_lstclear(&list, destroy_expand_token);
	return (raw_content);
}
