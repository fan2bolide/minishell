//
// Created by basil jeannot on 27/02/2023.
//

#include "minishell.h"

//only for debug purpose
//return the token array for the command " cat file1 | wc"
t_list *get_sample_tokens()
{
	t_list *res;
	t_token *token_array;

	ft_printf("\nsample cmd line : cat file1 | wc\n\n"); //debug

	token_array = malloc(sizeof(t_token) * 4);

	token_array[0].content = ft_strdup("cat");
	token_array[0].type = exec_name;

	token_array[1].content = ft_strdup("file1");
	token_array[1].type = arg;

	token_array[2].content = ft_strdup("|");
	token_array[2].type = operator_pipe;

	token_array[3].content = ft_strdup("wc");
	token_array[3].type = exec_name;

	res = ft_lstnew((void *)token_array);


	t_token *tok = NULL;

	for (int i = 1; i < 4; i++)
	{
		tok = &token_array[i];
		ft_lstadd_back(&res, ft_lstnew((void *)tok));
	}
	return res;
}
