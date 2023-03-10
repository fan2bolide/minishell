/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:44:06 by bajeanno          #+#    #+#             */
/*   Updated: 2023/02/27 21:44:09 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*evaluate_expression(char *expression, \
											t_token *prev);

t_type assign_operator_to_token(char const *expression)
{
	if (*expression == '$')
		return (env_variable);
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

t_token	*evaluate_expression(char *expression, t_token *prev)
{
	t_token	*curr;

	curr = malloc(sizeof (t_token));
	if (!curr)
		return (NULL);
	curr->content = set_token_content(expression);
	if (!expression || !*expression || !curr->content)
		return (curr->type = error, curr);
	if (ft_strchr(SPEC_CHAR, *expression))
		return (curr->type = assign_operator_to_token(expression), curr);
	if (!prev || ((prev->type == operator_pipe || prev->type == file)))
		return (curr->type = exec_name, curr);
	if (ft_strchr("<>", *(prev->content)))
		return (curr->type = file, curr);
	if (prev->type == exec_name || prev->type == arg)
		return (curr->type = arg, curr);
	return (curr->type = error, curr);
}

static size_t	get_next_expression(char *command_line)
{
	size_t	i;

	i = 0;
	if (!ft_strchr(SPEC_CHAR, *command_line))
		while ((command_line[i] && (!ft_strchr(SPEC_CHAR, command_line[i]) \
		|| command_line[i] == '$' || ft_strchr("\'\"", command_line[i])) && \
		!ft_isspace(command_line[i])))
		{
			if (ft_strchr("\'\"", command_line[i]))
				i += end_of_quote(command_line + i);
			if (!command_line[i])
				return (0);
			i++;
		}
	else
	{
		while (command_line[i] && *command_line == command_line[i])
			i++;
		if (*command_line == '$' && i == 1)
			while (command_line[i] && !ft_strchr(SPEC_CHAR, \
			command_line[i]) && !ft_isspace(command_line[i]))
				i++;
	}
	while (command_line[i] && ft_isspace(command_line[i]))
		i++;
	return (i);
}

t_list	*get_token_list(char *command_line)
{
	size_t	i;
	t_list	*list;
	t_list	*curr;

	if (!command_line || !*command_line)
		return (NULL);
	list = ft_lstnew(evaluate_expression(command_line, NULL));
	i = get_next_expression(command_line);
	curr = list;
	while (command_line[i])
	{
		curr->next = ft_lstnew(evaluate_expression(command_line + i, \
												   			curr->content));
		curr = curr->next;
		if (get_next_expression(command_line + i) == 0)
		{
			ft_printf("coucou je suis un fils de pute\n");
			return (ft_lstclear(&list, destroy_token), NULL);
		}
		i += get_next_expression(command_line + i);
	}
	return (list);
}

void	print_token(t_token *token)
{
	char	*token_type;

	token_type = "error, \t";
	if (token->type == exec_name)
		token_type = "exec_name, \t";
	if (token->type == arg)
		token_type = "arg, \t\t";
	if (token->type == file)
		token_type = "file, \t\t";
	if (token->type == operator_pipe)
		token_type = "operator_pipe, \t";
	if (token->type == redirect_out_append)
		token_type = "redirect_out_append, \t";
	if (token->type == redirect_in)
		token_type = "redirect_in, \t";
	if (token->type == redirect_out_trunc)
		token_type = "redirect_out_trunc, \t";
	if (token->type == redirect_hd)
		token_type = "redirect_hd, \t";
	if (token->type == env_variable)
		token_type = "env_variable, \t";
	ft_printf("%s%s\n", token_type, token->content);
}
