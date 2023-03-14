#include "minishell.h"
#include "expand.h"

static char *get_content(char *raw_content)
{
	int	i;
	char *new_content;

	i = 0;
	while (raw_content[i] && !ft_strchr("\'\"$", raw_content[i]))
		i++;
	new_content = ft_strnew(i);
	if (!new_content)
		return (NULL);
	ft_strncat(new_content, raw_content, i);
	return (new_content);
}

static t_expansion *evaluate_token(char *expression, t_expansion *prev)
{
	t_expansion *token;

	token = malloc(sizeof(t_expansion));
	if (!token)
		return (NULL);
	if (*expression == '\"')
		return (token->type = double_quote, token);
	if (*expression == '\'')
		return (token->type = quote, token);
	if (*expression == '$')
		return (token->type = dollar, token);
	if (prev && prev->type == dollar)
		return (token->type = word, token);
	return (token->content = get_content(expression), \
			token->type = word, token);
}

static size_t	get_next_token(char *token_content, t_expansion *prev)
{
	size_t	i;

	i = 0;
	if (ft_strchr("\'\"$", *token_content))
		return (1);
	if (prev && prev->type == dollar)
	{
		while (token_content[i] && !ft_strchr("\'\"$", token_content[i]) && \
			!ft_isspace(token_content[i]))
			i++;
		return (i);
	}
	while (token_content[i] && !ft_strchr("\'\"$", token_content[i]))
		i++;
	return (i);
}

t_list *get_token_list(char *raw_content)
{
	t_list	*list;
	t_list	*curr;
	size_t	i;

	list = ft_lstnew(evaluate_token(raw_content, NULL));
	i = get_next_token(raw_content, NULL);
	curr = list;
	while (raw_content[i])
	{
		curr->next = ft_lstnew(evaluate_token(raw_content + i, \
		((t_expansion *)curr->content)));
		i += get_next_token(raw_content + i, ((t_expansion *)curr->content));
		curr = curr->next;
	}
	return (list);
}

int	get_expanded_content(char *content)
{
	char *res;
	t_list *list;

	if (!ft_strchr(content, '$'))
		return (0);
	list = get_token_list(content);
	free(content);
	return (1);
}

void print_expand_token(t_expansion *token)
{
	char *res;

	if (token->type == double_quote)
		res = "double_quote";
	if (token->type == quote)
		res = "quote";
	if (token->type == dollar)
		res = "dollar";
	if (token->type == word)
		res = "word";
	ft_printf("%s, '%s'\n", res, token->content);
}

//int main()
//{
//	//todo : test avec plusieurs mots dans les guillemets
//	t_list *list = get_token_list("\"dsda$token das\"blabla");
//	t_list *curr = list;
//	while (curr)
//	{
//		print_expand_token((t_expansion *)curr->content);
//		curr = curr->next;
//	}
//	ft_printf("\n\n\n");
//	remove_quotes(&list);
//	return (0);
//}