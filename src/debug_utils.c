/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
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
			ft_printf("exec_name");
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
			ft_printf("redirect_out_trunc");
			break ;
		case 7:
			ft_printf("redirect_hd");
			break ;
		case 8:
			ft_printf("redirect_out_append");
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
void	log_cmd_lst(t_list *cmd_list)
{
	t_cmd	*current_cmd;
	int         node;

	node = 0;
	if (!cmd_list)
		return (ft_printf("log_cmd_lst failed (NULL pointer)\n"), (void)0);
	current_cmd = cmd_list->content;
	while(cmd_list)
	{
		ft_printf("node %d\n", node++);
		log_cmd(current_cmd);
		cmd_list = cmd_list->next;
		if (cmd_list)
			current_cmd = cmd_list->content;
	}
}

//debug
void	log_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return (ft_printf("log_cmd failed (NULL pointer)\n"), (void)0);
	//debug
	i = 0;
	while (cmd->argv[i] != NULL)
	{
		ft_printf("cmd->argv[%d] : %s\n", i, cmd->argv[i]); //debug
		i++;
	}
	if (cmd->redirect_in)
		ft_printf("cmd->redirect_in : %s\n", cmd->redirect_in);
	if (cmd->redirect_out)
	{
		ft_printf("cmd->redirect_out_trunc : %s\n", cmd->redirect_out);
		ft_printf("cmd->redirect_out_mode : ");
		switch (cmd->redirect_out_mode) {
			case 0:
				ft_printf("none\n");
				break;
			case 1:
				ft_printf("append\n");
				break;
			case 2:
				ft_printf("trunc\n");
				break;
		}

	}
	if (cmd->here_doc_mode)
		ft_printf("here_doc mode !\n");
}

//only for debug purpose
//return the token array for the command " cat file1 | wc"
t_list *get_sample_tokens()
{
	t_list *res;
	t_token *token_array;
	int 	size = 10;

	token_array = malloc(sizeof(t_token) * size);

	token_array[0].content = ft_strdup(">");
	token_array[0].type = redirect_out_trunc;

	token_array[1].content = ft_strdup("file1");
	token_array[1].type = file;

	token_array[2].content = ft_strdup("cat");
	token_array[2].type = exec_name;

	token_array[3].content = ft_strdup("-e");
	token_array[3].type = arg;

	token_array[4].content = ft_strdup("|");
	token_array[4].type = operator_pipe;

	token_array[5].content = ft_strdup("cat");
	token_array[5].type = exec_name;

	token_array[6].content = ft_strdup("-e");
	token_array[6].type = arg;

	token_array[7].content = ft_strdup("-a");
	token_array[7].type = arg;

	token_array[8].content = ft_strdup("<");
	token_array[8].type = redirect_in;

	token_array[9].content = ft_strdup("file2");
	token_array[9].type = file;

	res = ft_lstnew((void *)token_array);


	t_token *tok = NULL;

	ft_printf("\nsample exec_name line : %s ", token_array[0].content); //debug
	for (int i = 1; i < size; i++)
	{
		tok = &token_array[i];
		ft_lstadd_back(&res, ft_lstnew((void *)tok));
		ft_printf(tok->content);
		ft_printf(" ");
	}
	ft_printf("\n");
	return res;
}