//
// Created by basil jeannot on 24/02/2023.
//

#include "lexer.h"

static t_type	file_or_cmd(char *expression, t_token *prev);

static t_token	*evaluate_expression(char *expression, \
											t_token *prev);

t_type	file_or_cmd(char *expression, t_token *prev)
{
	size_t	i;

	i = 0;
	while (ft_isalpha(expression[i]))
		i++;
	while (ft_isspace(expression[i]))
		i++;
	if (expression[i] == '<')
		return (file);
	return (cmd);
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
		return (curr->type = operator, curr);
	if (!prev || (ft_strchr("|", *(prev->content)) && \
	ft_isalpha(expression[i])))
		return (curr->type = file_or_cmd(expression, prev), curr);
	if (ft_strchr("<>", *(prev->content)) && ft_isalpha(expression[i]))
		return (curr->type = file, curr);
	if (prev->type == cmd || prev->type == args)
		return (curr->type = args, curr);
	while (ft_isspace(expression[i]))
		i++;
	return (curr->type = error, curr);
}

static size_t	get_next_expression(char *command_line)
{
	size_t	i;

	i = 0;
	if (ft_isalpha(*command_line) || *command_line == '-')
		while (command_line[i] && (ft_isalpha(command_line[i]) || \
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

	if (token->type == cmd)
		token_type = "cmd, ";
	if (token->type == args)
		token_type = "args, ";
	if (token->type == file)
		token_type = "file, ";
	if (token->type == operator)
		token_type = "operator, ";
	ft_printf(token_type);
}

int	main(void)
{
	char *input = get_next_line(0);
	t_list *list;
	list = get_token_list(input);
	t_list *curr;
	curr = list;
	while (curr)
	{
		if (((t_token *)curr->content)->type == error)
			return (free(input), ft_lstclear(&list, free), 1);
		curr = curr->next;
	}
	curr = list;
	while (curr)
	{
		print_token(curr->content);
		curr = curr->next;
	}
	ft_printf("\n");
	return (0);
}
