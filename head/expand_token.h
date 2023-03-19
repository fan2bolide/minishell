#ifndef MINISHELL_EXPAND_TOKEN_H
#define MINISHELL_EXPAND_TOKEN_H

typedef enum e_expand_token_type
{
	double_quote,
	quote,
	word,
}	t_token_type;

typedef struct s_expansion
{
	t_token_type	type;
	char			*content;
}	t_expansion;

void	print_expand_token(t_expansion *token);
char	*expand_content(char *raw_content);
void	remove_quotes(t_list *token_list);
int		replace_with_value(void *expansion_token);
char	*join_contents(t_list *token_list);

#endif
