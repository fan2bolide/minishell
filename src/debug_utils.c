/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_token_lst_into_to_exec_lst_by_pipes.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 23:33:32 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//shall NOT be submitted in the vogosphere
//do NOT try to norm this file
//for debug purpose only


//debug
void	log_token(t_token *token)
{
	ft_printf("content\t: %s\n", token->content);
	ft_printf("type\t: ");
	switch (token->type)
	{
		case 0:
			ft_printf("error");
			break ;
		case 1:
			ft_printf("cmd");
			break ;
		case 2:
			ft_printf("arg");
			break ;
		case 3:
			ft_printf("file");
			break ;
		case 4:
			ft_printf("operator_pipe");
			break ;
		case 5:
			ft_printf("redirect_in");
			break ;
		case 6:
			ft_printf("redirect_out");
			break ;
		case 7:
			ft_printf("redirect_hd");
			break ;
		case 8:
			ft_printf("redirect_append");
			break ;
		case 9:
			ft_printf("env_variable");
			break;
	}
	ft_printf("\n\n");
}

//debug
void	log_token_list(t_list *token_list)
{
	t_token	*token_ptr;
	t_list	*token_list_cursor;

	token_ptr = (t_token *)token_list->content;
	log_token(token_ptr);
	token_list_cursor = token_list->next;
	while (token_list_cursor)
	{
		token_ptr = (t_token *)token_list_cursor->content;
		log_token(token_ptr);
		token_list_cursor = token_list_cursor->next;
	}
}

//debug
void	log_to_exec_lst(t_list *to_exec_list)
{
	t_to_exec	*current_to_exec;
	int         node;

	node = 0;
	if (!to_exec_list)
		return (ft_printf("log_to_exec_lst failed (NULL pointer)\n"), (void)0);
	current_to_exec = to_exec_list->content;
	while(to_exec_list)
	{
		ft_printf("node %d\n", node++);
		log_to_exec(current_to_exec);
		to_exec_list = to_exec_list->next;
		if (to_exec_list)
			current_to_exec = to_exec_list->content;
	}
}

//debug
void	log_to_exec(t_to_exec *to_exec)
{
	int	i;

	if (!to_exec)
		return (ft_printf("log_to_exec failed (NULL pointer)\n"), (void)0);
	//debug
	i = 0;
	while (to_exec->cmd[i] != NULL)
	{
		ft_printf("to_exec->cmd[%d] : %s\n", i, to_exec->cmd[i]); //debug
		i++;
	}
}

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