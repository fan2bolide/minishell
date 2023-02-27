//
// Created by basil jeannot on 27/02/2023.
//

#include "lexer.h"

char	*get_token_content(char *expression)
{
	size_t	i;
	char	*content;

	i = 0;
	if (ft_isalpha(*expression) || *expression == '-')
		while (expression[i] && (ft_isalpha(expression[i]) || \
		expression[i] == '-'))
			i++;
	else
		if (ft_strchr(SPEC_CHAR, *expression))
			while (expression[i] && *expression == expression[i])
				i++;
		else
			return (NULL);
	content = ft_strnew(i--);
	if (!content)
		return (NULL);
	ft_strncpy(expression, content, i);
	return (content);
}