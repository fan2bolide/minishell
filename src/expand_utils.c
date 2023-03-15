#include "libft.h"
#include "expand_token.h"

void destroy_expand_token(void *token)
{
	t_expansion *to_destroy;

	to_destroy = token;
	free(to_destroy->content);
	free(to_destroy);
}

void remove_quotes(t_list *token_list)
{
	while (token_list)
	{
		if (((t_expansion *)token_list->content)->type == quote)
			((t_expansion *)token_list->content)->content = \
			ft_strtrim(((t_expansion *)token_list->content)->content, "\'");
		if (((t_expansion *)token_list->content)->type == double_quote)
			((t_expansion *)token_list->content)->content = \
			ft_strtrim(((t_expansion *)token_list->content)->content, "\"");
		token_list = token_list->next;
	}
}

char *join_contents(t_list *token_list)
{
	char *res;
	char *to_destroy;

	to_destroy = ft_calloc(1, 1);
	while (token_list)
	{
		res = ft_strjoin(to_destroy, \
		((t_expansion *)token_list->content)->content);
		to_destroy = res;
		token_list = token_list->next;
	}
	return (res);
}

char *get_value_of_var(char *var)
{
	char *value;
	char *var_name;
	int i;

	i = 0;
	while (var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	var_name = ft_strnew(i);
	var_name = ft_strncpy(var, var_name, i);
	value = getenv(var_name);
	free(var_name);
	return (value);
}

int replace_with_value(void *expansion_token)
{
	t_expansion	*token;
	char *token_content;
	size_t		i;
	char		*tmp;
	char		*value;

	token = expansion_token;
	if (token->type != quote)
	{
		if (!ft_strchr(token->content, '$'))
			return (1);
		tmp = ft_strnew(0);
		token_content = token->content;
		i = 0;
		while (token->content[i])
		{
			token->content += i;
			i = 0;
			while (token->content[i] && token->content[i] != '$')
				i++;
			ft_strncat(tmp, token->content, (int)i);
			i++;
			value = get_value_of_var(token->content + i);
			if (!value)
				value = "";
			ft_strcat(tmp, value);
			while (token->content[i] && (ft_isalnum(token->content[i]) || \
					token->content[i] == '_'))
				i++;
		}
		free(token_content);
		token->content = tmp;
	}
	return (1);
}