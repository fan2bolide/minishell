//
// Created by basil jeannot on 27/02/2023.
//

#include "lexer.h"

static void	destroy_token(void *token);

char	*get_token_content(char *expression)
{
	size_t	i;
	char	*content;

	i = 0;
	if (ft_isalnum(*expression) || *expression == '-')
		while (expression[i] && (ft_isalnum(expression[i]) || \
		expression[i] == '-'))
			i++;
	else
		if (ft_strchr(SPEC_CHAR, *expression))
			while (expression[i] && *expression == expression[i])
				i++;
		else
			return (NULL);
	content = ft_strnew(i);
	if (!content)
		return (NULL);
	ft_strncpy(expression, content, i);
	return (content);
}

void	destroy_token_list(t_token **token_list)
{
	ft_lstclear(token_list, destroy_token);
	free(*token_list);
}

static void	destroy_token(void *token)
{
	t_token *tmp;
	tmp = token;

	free(tmp->content);
	free(tmp);
}