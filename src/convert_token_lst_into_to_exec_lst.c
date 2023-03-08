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

static void	switch_case(t_list *token_lst_cursor, t_list **to_exec_lst);
void		case_current_token_type_is_exec_name(
		t_list *token_lst_cursor, t_to_exec *to_exec); //static ?
void    case_current_token_type_is_redirect_out(
		t_list *token_lst_cursor, t_to_exec *to_exec); //static ?
void	case_current_token_type_is_redirect_in(
		t_list *token_lst_cursor, t_to_exec *to_exec);
static int token_is_null(void *token_lst_content);

t_list 	*convert_token_lst_into_to_exec_lst(t_list *token_lst)
{
	t_list *to_exec_lst;
	t_list  *res;

	to_exec_lst = ft_lstnew(NULL);
	res = to_exec_lst;
	to_exec_lst->content = malloc(sizeof (t_to_exec));
	while (token_lst)
	{
		switch_case(token_lst, &to_exec_lst);
		token_lst = token_lst->next;
	}
	log_to_exec_lst(res);
	return (res);
}

static void	switch_case(t_list *token_lst_cursor, t_list **to_exec_lst)
{
	t_token *current_token;


	current_token = token_lst_cursor->content;
//    print_token(current_token);
	if (current_token->type == exec_name)
		case_current_token_type_is_exec_name(token_lst_cursor, (*to_exec_lst)->content);
	else if (current_token->type == arg)
	{ft_printf("\n");}//debug
	else if (current_token->type == redirect_out)
	{       case_current_token_type_is_redirect_out(token_lst_cursor, (*to_exec_lst)->content);}//debug
	else if (current_token->type == redirect_in)
	{ case_current_token_type_is_redirect_in(token_lst_cursor, (*to_exec_lst)->content);}//debug
	else if (current_token->type == operator_pipe)
	{
		(*to_exec_lst)->next = ft_lstnew(malloc(sizeof (t_to_exec))); // à protéger
		*to_exec_lst = (*to_exec_lst)->next;
	}
	else
		ft_printf("\t(switch case)another case\n");//debug
}

void		case_current_token_type_is_exec_name(
	t_list *token_lst_cursor, t_to_exec *to_exec)
{
	int		cmd_tab_size;
	t_token	*current_token;
	int		i;

	i = 0;
	cmd_tab_size = token_cmd_line_size(token_lst_cursor) + 1;
	to_exec->cmd = ft_calloc(cmd_tab_size, sizeof(char *));
	current_token = token_lst_cursor->content;
	while (cmd_tab_size > 1)
		{
			current_token = token_lst_cursor->content;
			to_exec->cmd[i++] = ft_strdup(current_token->content);
			token_lst_cursor = token_lst_cursor->next;
			cmd_tab_size--;
		}
	to_exec->cmd[i] = NULL;
}

void	case_current_token_type_is_redirect_out(
		t_list *token_lst_cursor, t_to_exec *to_exec)
{
	t_token *token_with_the_redirect_file;
	int open_mode;
	char	*operator;
	char *file;

	token_with_the_redirect_file = token_lst_cursor->next->content;
	file = token_with_the_redirect_file->content;
	operator = ((t_token *)(token_lst_cursor->content))->content;
	if (ft_strequ(operator, ">"))
		open_mode = trunc;
	if (ft_strequ(operator, ">>"))
		open_mode = append;
	to_exec->redirect_out = ft_strdup(file); // a proteger
	to_exec->redirect_out_mode = open_mode;
}


void	case_current_token_type_is_redirect_in(
		t_list *token_lst_cursor, t_to_exec *to_exec)
{
	t_token *token_with_the_redirect_file;
	char *file;

	token_with_the_redirect_file = token_lst_cursor->next->content;
	file = token_with_the_redirect_file->content;
	to_exec->redirect_in = ft_strdup(file); // a proteger
}