/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:44:06 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/11 04:39:03 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_type	assign_operator_to_token(char const *expression)
{
	if (*expression == '|')
		return (operator_pipe);
	if (*expression == '<')
	{
		if (expression[1] == '<')
			return (redirect_hd);
		else
			return (redirect_in);
	}
	if (*expression == '>')
	{
		if (expression[1] == '>')
			return (redirect_out_append);
		else
			return (redirect_out_trunc);
	}
	return (error);
}

t_token	*evaluate_expression(char *expression, t_token *prev, int is_exec_name)
{
	t_token	*curr;

	curr = malloc(sizeof(t_token));
	if (!curr)
		return (NULL);
	curr->content = create_token_content(expression);
	if (!expression || !*expression || !curr->content)
		return (curr->type = error, curr);
	if (ft_strchr(SPEC_CHAR, *expression) && *expression != '$')
		return (curr->type = assign_operator_to_token(expression), curr);
	if (!prev || prev->type == operator_pipe || (prev->type == file
			&& !is_exec_name))
		return (curr->type = exec_name, curr);
	if (ft_strchr("<>", *(prev->content)))
		return (curr->type = file, curr);
	if (prev->type == exec_name || prev->type == arg || prev->type == file)
		return (curr->type = arg, curr);
	return (curr->type = error, curr);
}

static size_t	skip_whitespaces(char *command_line)
{
	size_t	i;

	i = 0;
	while (command_line[i] && ft_isspace(command_line[i]))
		i++;
	return (i);
}

size_t	get_next_expression(char *command_line)
{
	size_t	i;

	i = 0;
	if (!ft_strchr(SPEC_CHAR, *command_line) || *command_line == '$')
	{
		while ((command_line[i] && (!ft_strchr(SPEC_CHAR, command_line[i])
					|| command_line[i] == '$' || ft_strchr("\'\"",
						command_line[i])) && !ft_isspace(command_line[i])))
		{
			i += end_of_quote(command_line + i);
			if (!command_line[i])
				return (0);
			i++;
		}
	}
	else
	{
		while (command_line[i] && *command_line == command_line[i])
			i++;
		if (*command_line == '$' && i == 1)
			while (command_line[i] && !ft_strchr(SPEC_CHAR, command_line[i])
				&& !ft_isspace(command_line[i]))
				i++;
	}
	return (i + skip_whitespaces(command_line + i));
}
