//
// Created by basil jeannot on 24/02/2023.
//

#include "lexer.h"

static t_type file_or_cmd(char *expression, t_token *prev);

static t_token	*evaluate_expression(char *expression,\
											t_token *prev)
{
	size_t	i;
	t_token	*curr;

	curr = malloc(sizeof (t_token));
	if (!curr)
		return (NULL);
	curr->content = expression;
	i = 0;
	if (expression == NULL)
		return (NULL);
	if (ft_strchr(SPEC_CHAR, expression[i]))//a voir pour le dollar
		return (curr->type = operator, curr);
	if (!prev)
		return (curr->type = file_or_cmd(expression, prev), curr);
	if (prev->type == operator)
	{
		if (ft_strchr("<>", *(prev->content)) && ft_isalpha(expression[i]))
			return (curr->type = file, curr);
		else
			return ()
	}
	while (ft_isspace(expression[i]))
		i++;
	return (NULL);
}

static t_type file_or_cmd(char *expression, t_token *prev) {
	size_t i;

	i = 0;
	while (ft_isalpha(expression[i]))
		i++;
	while (ft_isspace(expression[i]))
		i++;
	if (expression[i] == '<')
		return (file);
	return cmd;
}

t_list *tokenize_command(char *command_line)
{

}

int main()
{
	char *input = get_next_line(0);
	evaluate_expression(input, 0);
	ft_printf("\n", evaluate_expression(input, 2));
	return (0);
}
