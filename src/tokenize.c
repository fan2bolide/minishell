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
			return (redirect_append);
		else
			return (redirect_out);
	}
	return (error);
}

t_token	*evaluate_expression(char *expression, t_token *prev)
{
	size_t	i;
	t_token	*curr;

	if (!expression)
		return (NULL);
	curr = malloc(sizeof (t_token));
	if (!curr)
		return (NULL);
	curr->content = get_token_content(expression);
	i = 0;
	if (ft_strchr(SPEC_CHAR, expression[i]))//TODO: a voir pour le dollar
		return (curr->type = assign_operator_to_token(expression), curr);
	if (!prev || ((ft_strchr("|", *(prev->content)) || prev->type == file) && \
	ft_isalnum(expression[i])))
		return (curr->type = exec_name, curr);
	if (ft_strchr("<>", *(prev->content)) && ft_isalnum(expression[i]))
		return (curr->type = file, curr);
	if (prev->type == exec_name || prev->type == arg)
		return (curr->type = arg, curr);
	while (ft_isspace(expression[i]))
		i++;
	return (curr->type = error, curr);
}

static size_t	get_next_expression(char *command_line)
{
	size_t	i;

	i = 0;
	if (ft_strchr("\"", *command_line))
	{
		i++;
		while (!ft_strchr("\"", command_line[i]))
			i++;
	}
	if (ft_isalnum(*command_line) || *command_line == '-')
		while (command_line[i] && (ft_isalnum(command_line[i]) || \
		command_line[i] == '-'))
			i++;
	else
		if (ft_strchr(SPEC_CHAR, *command_line))
			while (command_line[i] && *command_line == command_line[i])
				i++;
		else
			return (0);
	while (command_line[i] && ft_isspace(command_line[i]))
		i++;
	return (i);
}

t_list	*get_token_list(char *command_line)
{
	size_t	i;
	t_list	*list;
	t_list	*curr;

	list = ft_lstnew(evaluate_expression(command_line, NULL));
	i = get_next_expression(command_line);
	curr = list;
	while (command_line[i])
	{
		curr->next = ft_lstnew(evaluate_expression(command_line + i, \
																curr->content));
		curr = curr->next;
		i += get_next_expression(command_line + i);
		if (i == 0) //todo : gestion d'erreur
			return (NULL);
	}
	return (list);
}

void	print_token(t_token *token)
{
	char	*token_type;

	if (token->type == exec_name)
		token_type = "exec_name, ";
	if (token->type == arg)
		token_type = "arg, ";
	if (token->type == file)
		token_type = "file, ";
	if (token->type == operator_pipe)
		token_type = "operator_pipe, ";
	if (token->type == redirect_append)
		token_type = "redirect_append, ";
	if (token->type == redirect_in)
		token_type = "redirect_in, ";
	if (token->type == redirect_out)
		token_type = "redirect_out, ";
	if (token->type == redirect_hd)
		token_type = "redirect_hd, ";
	ft_printf("%s%s\n", token_type, token->content);
}
