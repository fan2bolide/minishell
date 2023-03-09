/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_token_lst_into_cmd_lst.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 23:33:32 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	switch_case(t_list *token_lst_cursor, t_list **cmd_lst, char **envp);
void		case_current_token_type_is_exec_name(
		t_list *token_lst_cursor, t_cmd *cmd, char **envp); //static ?
void    case_current_token_type_is_redirect_out(
		t_list *token_lst_cursor, t_cmd *cmd); //static ?
void	case_current_token_type_is_redirect_in(
		t_list *token_lst_cursor, t_cmd *cmd);
static int token_is_null(void *token_lst_content);

t_list 	*convert_token_lst_into_cmd_lst(t_list *token_lst, char **envp)
{
	t_list *cmd_lst;
	t_list  *res;

	cmd_lst = ft_lstnew(NULL);
	res = cmd_lst;
	cmd_lst->content = create_new_cmd(envp);
	while (token_lst)
	{
		switch_case(token_lst, &cmd_lst, envp);
		token_lst = token_lst->next;
	}
	log_cmd_lst(res);
	return (res);
}

static void	switch_case(t_list *token_lst_cursor, t_list **cmd_lst, char **envp)
{
	t_token *current_token;


	current_token = token_lst_cursor->content;
	if (current_token->type == exec_name)
		case_current_token_type_is_exec_name(token_lst_cursor, (*cmd_lst)->content, envp);
	else if (current_token->type == arg)
	{ft_printf("\n");}//debug
	else if (current_token->type == redirect_out)
	{       case_current_token_type_is_redirect_out(token_lst_cursor, (*cmd_lst)->content);}//debug
	else if (current_token->type == redirect_in)
	{ case_current_token_type_is_redirect_in(token_lst_cursor, (*cmd_lst)->content);}//debug
	else if (current_token->type == operator_pipe)
	{
		(*cmd_lst)->next = ft_lstnew(malloc(sizeof (t_cmd))); // à protéger
		*cmd_lst = (*cmd_lst)->next;
	}
	else
		ft_printf("\t(switch case)another case\n");//debug
}

void		case_current_token_type_is_exec_name(
		t_list *token_lst_cursor, t_cmd *cmd, char **envp)
{
	int		cmd_tab_size;
	t_token	*current_token;
	int		i;

	i = 0;
	cmd_tab_size = token_cmd_line_size(token_lst_cursor) + 1;
	cmd->argv = ft_calloc(cmd_tab_size, sizeof(char *));
	current_token = token_lst_cursor->content;
	while (cmd_tab_size > 1)
		{
			current_token = token_lst_cursor->content;
			cmd->argv[i++] = ft_strdup(current_token->content);
			token_lst_cursor = token_lst_cursor->next;
			cmd_tab_size--;
		}
	cmd->argv[i] = NULL;
	cmd->path = get_path(cmd->argv[0], envp);
}

void	case_current_token_type_is_redirect_out(
		t_list *token_lst_cursor, t_cmd *cmd)
{
	t_token *token_with_the_redirect_file;
	int open_mode;
	char	*operator;
	char *file;

	token_with_the_redirect_file = token_lst_cursor->next->content;
	file = token_with_the_redirect_file->content;
	operator = ((t_token *)(token_lst_cursor->content))->content;
	if (ft_strequ(operator, ">"))
		open_mode = O_TRUNC;
	if (ft_strequ(operator, ">>"))
		open_mode = O_APPEND;
	cmd->redirect_out = ft_strdup(file); // a proteger
	cmd->redirect_out_mode = open_mode;
}


void	case_current_token_type_is_redirect_in(
		t_list *token_lst_cursor, t_cmd *cmd)
{
	t_token *token_with_the_redirect_file;
	char *file;

	token_with_the_redirect_file = token_lst_cursor->next->content;
	file = token_with_the_redirect_file->content;
	cmd->redirect_in = ft_strdup(file); // a proteger
}