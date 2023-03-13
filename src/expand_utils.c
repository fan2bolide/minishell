#include "libft.h"
#include "expand.h"

void destroy_token(void *token)
{
	free(((t_expansion *)token)->content);
	free(((t_expansion *)token));
}

void remove_quotes(t_list **token_list)
{
	t_list *curr;
	t_list *remove;

	curr = *token_list;
	if (curr && curr->next && curr->next->next && curr->next->next->next)
	{
		if (((t_expansion *)curr->content)->type == double_quote && \
		((t_expansion *)curr->next->content)->type == dollar && \
		((t_expansion *)curr->next->next->content)->type == word && \
		((t_expansion *)curr->next->next->next->content)->type == double_quote)
		{
			ft_printf("removing : ");
			print_expand_token(((t_expansion *)curr->content));
			ft_lstpop_front(token_list, destroy_token);
			curr = *token_list;
			curr = curr->next;
			remove = curr->next;
			curr->next = remove->next;
			ft_printf("removing : ");
			print_expand_token(((t_expansion *)remove->content));
			ft_lstdelone(remove, destroy_token);
		}
	}
	curr = *token_list;
	while (curr)
	{
		print_expand_token(curr->content);
		curr = curr->next;
	}
}
//
//void
//
//void replace_with_value()