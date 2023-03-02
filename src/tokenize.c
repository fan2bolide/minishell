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

	curr = malloc(sizeof (t_token));
	if (!curr)
		return (NULL);
	curr->content = get_token_content(expression);
	if (!expression || !*expression || !curr->content)
	{
		return (curr->type = error, curr);
	}
	i = 0;
	if (ft_strchr(SPEC_CHAR, *expression))
		return (curr->type = assign_operator_to_token(expression), curr);
	if (!prev || ((prev->type == operator_pipe || \
	prev->type == file) && (ft_isalnum(*expression) || \
	ft_strchr("./-_\"", *expression))))
		return (curr->type = exec_name, curr);
	if (ft_strchr("<>", *(prev->content)) && (ft_isalnum(*expression) || \
		ft_strchr("./-_", *expression)))
		return (curr->type = file, curr);
	ft_printf("\n\nexpression : %s\nprev = %s\n", expression, prev->content);
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
		while (command_line[i] && !ft_strchr("\"", command_line[i]))
			i++;
		if (!command_line[i++])
			return (0);
	}
	else
	{
		if (ft_isalnum(*command_line) || ft_strchr("./-_", command_line[i]))
			while (command_line[i] && (ft_isalnum(command_line[i]) || \
			ft_strchr("./-_", command_line[i])))
				i++;
		else
			if (ft_strchr(SPEC_CHAR, *command_line))
				while (command_line[i] && *command_line == command_line[i])
					i++;
			else
				return (0);
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

	list = ft_lstnew(evaluate_expression(command_line, NULL));
	i = get_next_expression(command_line);
	curr = list;

	while (command_line[i])
	{
		curr->next = ft_lstnew(\
		evaluate_expression(command_line + i, curr->content));
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
		token_type = "exec_name, \t";
	if (token->type == arg)
		token_type = "arg, \t\t";
	if (token->type == file)
		token_type = "file, \t\t";
	if (token->type == operator_pipe)
		token_type = "operator_pipe, \t";
	if (token->type == redirect_append)
		token_type = "redirect_append, \t";
	if (token->type == redirect_in)
		token_type = "redirect_in, \t";
	if (token->type == redirect_out)
		token_type = "redirect_out, \t";
	if (token->type == redirect_hd)
		token_type = "redirect_hd, \t";
	ft_printf("%s%s\n", token_type, token->content);
}
