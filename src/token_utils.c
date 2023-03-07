/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:43:40 by bajeanno          #+#    #+#             */
/*   Updated: 2023/02/27 21:44:16 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	destroy_token(void *token);

char	*set_token_content(char *expression)
{
	size_t	i;
	char	*content;

	i = 0;
	//todo : faire une fonction pour ces cas là
	if (ft_strchr("\"", *expression))
	{
		i++;
		while (expression[i] && !ft_strchr("\"", expression[i]))
			i++;
		if (!expression[i])
			return (NULL);
		else
			i++;
	}
	else
	{
		if (ft_strchr("\'", *expression))
		{
			i++;
			while (expression[i] && !ft_strchr("\'", expression[i]))
				i++;
			if (!expression[i])
				return (NULL);
			else
				i++;
		}
		else
			if (ft_isalnum(*expression) || ft_strchr("./-_=", *expression))
				while (expression[i] && (ft_isalnum(expression[i]) || \
				ft_strchr("./-_=", expression[i])))
					i++;
			else
				if (ft_strchr(SPEC_CHAR, *expression))
					while (expression[i] && *expression == expression[i])
						i++;
				else
					return (NULL);
	}
	content = ft_strnew(i);
	if (!content)
		return (NULL);
	ft_strncpy(expression, content, (int)i);
	return (ft_strtrim(content, " "));
}

void	destroy_token_list(t_list *token_list)
{
	ft_lstclear(&token_list, destroy_token);
}

static void	destroy_token(void *token)
{
	free(((t_token *)token)->content);
	free(token);
}

// for a cmd line (given into a token-list format),
// returns 1(for the exec_name) + the number of args following the exec_name
//ex : "echo te quiero loco | ... ": returns 4
//ex : "ls | ..." : returns only 1
//ex : "< file | ..." : returns 0
int	token_cmd_line_size(t_list *token_lst)
{
    int	res;

    res = 0;
    if (((t_token *)token_lst->content)->type != exec_name)
        return (0);
    res++;
    token_lst = token_lst->next;
    while (token_lst && ((t_token *)token_lst->content)->type == arg)
    {
        res++;
        token_lst = token_lst->next;
    }
    return (res);
}
