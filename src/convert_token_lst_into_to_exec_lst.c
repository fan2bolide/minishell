/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_token_lst_into_to_exec_lst.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 23:33:32 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	switch_case(t_list *token_lst_cursor, t_to_exec *current_to_exec);
void		case_current_token_type_is_exec_name(
		t_list *token_lst_cursor, t_to_exec *to_exec); //static ?
void    case_current_token_type_is_redirect_out(
        t_list *token_lst_cursor, t_to_exec *to_exec); //static ?
t_to_exec	*convert_token_lst_into_to_exec_lst(t_list *token_lst)
{
	t_list		*to_exec_lst;
	t_to_exec	*current_to_exec;
	t_token		*current_token;
	t_list		*token_lst_cursor;

	ft_printf("converting token_lst into to_exec_lst\n"); //debug
	ft_printf("\n\n\n\n");     //debug
	token_lst_cursor = token_lst;
	current_token = token_lst->content;
	to_exec_lst = ft_lstnew(NULL);
	current_to_exec = malloc(sizeof(t_to_exec));
	to_exec_lst->content = current_to_exec;
    //TODO : now we need to fetch whats after a pipe and put it in a new node of to_exec_lst
	while (current_token->type != operator_pipe)
	{
		switch_case(token_lst_cursor, current_to_exec);
        ft_printf("(convert..)to_exec->cmd[0] : %s\n", current_to_exec->cmd[0]);//debug
		token_lst_cursor = token_lst_cursor->next;
		current_token = token_lst_cursor->content;
	}
    ft_printf("\n\n(convert end)logging to_exec_lst : \n"); //debug
	log_to_exec_lst(to_exec_lst);
	// current_to_exec->content;
	// current_token = current_token->next;
	// current_to_exec =
}

static void	switch_case(t_list *token_lst_cursor, t_to_exec *to_exec) {
    t_token *current_token;

    current_token = token_lst_cursor->content;
    ft_printf("\t(switch case)\nCurrent token :\n"); //debug
    print_token(current_token);
    if (current_token->type == exec_name)
        case_current_token_type_is_exec_name(token_lst_cursor, to_exec);
    else if (current_token->type == arg)
    {       ft_printf("\t(switch case)this is an arg, nothing to do\n");}//debug
     else if (current_token->type == redirect_out)
    {       case_current_token_type_is_redirect_out(token_lst_cursor, to_exec);}//debug
    else if (current_token->type == redirect_in)
    {       ft_printf("\t(switch case)this is an arg, nothing to do\n");}//debug
    else if (current_token->type == operator_pipe)
    {       ft_printf("\t(switch case)this is a pipe, nothing to do\n");}//debug
    else
    {
        ft_printf("\t(switch case)another case\n");//debug
    }
}

void		case_current_token_type_is_exec_name(
	t_list *token_lst_cursor, t_to_exec *to_exec)
{
	int		cmd_tab_size;
	t_token	*current_token;
	int		i;

	ft_printf("\t\t(case \"current_token->type == exec_name\")\n"); //debug
	i = 0;
	cmd_tab_size = token_cmd_line_size(token_lst_cursor) + 1;
	to_exec->cmd = ft_calloc(cmd_tab_size, sizeof(char *));
    current_token = token_lst_cursor->content;
	while (cmd_tab_size > 1)
		{
			current_token = token_lst_cursor->content;
            to_exec->cmd[i++] = current_token->content; //maybe strdup instead of copying the adresss
			token_lst_cursor = token_lst_cursor->next;
			cmd_tab_size--;
		}
    to_exec->cmd[i] = NULL;
}

void    case_current_token_type_is_redirect_out(
        t_list *token_lst_cursor, t_to_exec *to_exec)
{
    t_token *token_with_the_redirect_file;

    token_with_the_redirect_file = token_lst_cursor->next->content; //todo : set the redirect file into to_exec->redirect_out,
    // and do the same for every kind of redirections
//    to_exec->redirect_out = ft_strdup(to)
}