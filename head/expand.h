#ifndef MINISHELL_EXPAND_H
#define MINISHELL_EXPAND_H

typedef enum e_expand_token_type
{
	double_quote,
	quote,
	word,
	dollar
}	t_token_type;

typedef struct s_expansion
{
	t_token_type	type;
	char			*content;
}	t_expansion;

void print_expand_token(t_expansion *token);
void remove_quotes(t_list **token_list);

#endif
