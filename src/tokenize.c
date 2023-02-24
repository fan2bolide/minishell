//
// Created by basil jeannot on 24/02/2023.
//

#include "lexer.h"

static t_tokened_unit	evaluate_expression(char *expression, t_type \
prev_expression_type)
{

}

static size_t	count_expressions(char *command_line)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	while (command_line[i])
	{
		if (ft_strchr(SPEC_CHAR, command_line[i]))
		{
			count++;
			i+=2;
		}
		if (command_line[i] == '"')
		{
			i++;
			while (command_line[i] && command_line[i] != '"')
				i++;
			count++;
		}
		if (command_line[i] == '\'')
		{
			i++;
			while (command_line[i] && command_line[i] != '\'')
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

//t_tokened_unit	*tokenize_command(char *command_line)
//{
//
//}

int main()
{
	char *input = get_next_line(0);
	ft_printf("count = %d\n", count_expressions(input));
	return (0);
}
