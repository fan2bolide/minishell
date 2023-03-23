#ifndef EXPAND_TOKEN_H
#define EXPAND_TOKEN_H

# include "minishell.h"

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

void	destroy_expand_token(void *token);
void	remove_quotes(t_list *token_list);
int		replace_with_value(void *expansion_token, t_list **envp);
char	*join_contents(t_list *token_list);

#endif
