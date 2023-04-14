/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_token_lst_into_cmd_lst.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/04/12 01:59:35 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

static void		\
switch_case(t_token_list *token_lst_cursor, t_cmd_list **cmd_lst);
static void		\
case_current_token_type_is_exec_name(t_token_list *token_lst_cursor, \
t_cmd *cmd);
static void		\
case_current_token_type_is_redirect_out( \
t_token_list *token_lst_cursor, t_cmd *cmd);
static void		\
case_current_token_type_is_redirect_in( \
t_token_list *token_lst_cursor, t_cmd *cmd);
static void		\
case_current_token_type_is_redirect_hd(t_cmd_list **cmd_lst, \
t_token_list *token_lst_cursor);

t_cmd_list	*convert_token_lst_into_cmd_lst(t_token_list *token_lst)
{
	t_cmd_list	*cmd_lst;
	t_cmd_list	*res;

	cmd_lst = (t_cmd_list *)ft_lstnew(NULL);
	res = cmd_lst;
	cmd_lst->content = create_new_cmd();
	while (token_lst)
	{
		switch_case(token_lst, &cmd_lst);
		token_lst = token_lst->next;
	}
	return (res);
}

static void	switch_case(t_token_list *token_lst_cursor, t_cmd_list **cmd_lst)
{
	t_token	*current_token;

	if (!*cmd_lst)
		return ;
	current_token = token_lst_cursor->content;
	if (current_token->type == exec_name)
		case_current_token_type_is_exec_name(token_lst_cursor,
			(*cmd_lst)->content);
	else if (current_token->type == redirect_out_trunc
		|| current_token->type == redirect_out_append)
	{
		case_current_token_type_is_redirect_out(token_lst_cursor,
			(*cmd_lst)->content);
	}
	else if (current_token->type == redirect_in)
	{
		case_current_token_type_is_redirect_in(token_lst_cursor,
			(*cmd_lst)->content);
	}
	else if (current_token->type == operator_pipe)
	{
		(*cmd_lst)->next = (t_cmd_list *)ft_lstnew(create_new_cmd());
		if (!(*cmd_lst)->next)
			return print_error(error_occured, NULL);
		*cmd_lst = (*cmd_lst)->next;
	}
	else if (current_token->type == redirect_hd)
		case_current_token_type_is_redirect_hd(cmd_lst, token_lst_cursor);
}

void	case_current_token_type_is_redirect_hd(t_cmd_list **cmd_lst,
											t_token_list *token_lst_cursor)
{
	(*cmd_lst)->content->heredoc_mode = 1;
	(*cmd_lst)->content->heredoc_delim = ft_strdup(token_lst_cursor->next->content->content);
	if (!(*cmd_lst)->content->heredoc_delim && token_lst_cursor->next->content->content)
		return (print_error(error_occured, "heredoc error"));
	pipe((*(*cmd_lst)->content).heredoc_pipe);
	manage_here_doc(*(*cmd_lst)->content);
	if (!(*cmd_lst)->content->path)
		(*cmd_lst)->content->path = ft_strdup("heredoc");
	if (!(*cmd_lst)->content->argv)
		(*cmd_lst)->content->argv = NULL;
}

void	case_current_token_type_is_exec_name(t_token_list *token_lst_cursor,
											t_cmd *cmd)
{
	size_t	cmd_tab_size;
	t_token	*current_token;
	char	**splits;
	int		i;
	int		j;

	i = 0;
	cmd_tab_size = token_cmd_line_size(token_lst_cursor) + 1;
	cmd->argv = ft_calloc(cmd_tab_size, sizeof(char *));
	if (cmd_tab_size > 1)
	{
		current_token = token_lst_cursor->content;
		splits = ft_old_split(current_token->content, ' ');
		j = 0;
		while (splits[j])
		{
			cmd->argv[i++] = splits[j++];
			cmd_tab_size--;
		}
		token_lst_cursor = token_lst_cursor->next;
		free(splits);
	}
	while (cmd_tab_size > 1)
	{
		current_token = token_lst_cursor->content;
		cmd->argv[i++] = ft_strdup(current_token->content);
		token_lst_cursor = token_lst_cursor->next;
		cmd_tab_size--;
	}
	cmd->argv[i] = NULL;
	free(cmd->path);
	if (is_builtin(cmd->argv[0]) < 0)
		cmd->path = get_path(cmd->argv[0], g_envp_lst);
	else
		cmd->path = ft_strdup("builtin"); //todo protect this
}

void	case_current_token_type_is_redirect_out(
	t_token_list *token_lst_cursor, t_cmd *cmd)
{
	t_token	*token_with_the_redirect_file;
	int		open_mode;
	char	*file;

	token_with_the_redirect_file = token_lst_cursor->next->content;
	file = token_with_the_redirect_file->content;
	if (token_lst_cursor->content->type == redirect_out_trunc)
		open_mode = O_TRUNC;
	if (token_lst_cursor->content->type == redirect_out_append)
		open_mode = O_APPEND;
	free(cmd->redirect_out);
	cmd->redirect_out = ft_strdup(file); //todo protect this
	cmd->redirect_out_mode = open_mode;
}

void		case_current_token_type_is_redirect_in(
	t_token_list *token_lst_cursor, t_cmd *cmd)
{
	t_token	*token_with_the_redirect_file;
	char	*file;

	token_with_the_redirect_file = token_lst_cursor->next->content;
	file = token_with_the_redirect_file->content;
	cmd->redirect_in = ft_strdup(file); //todo protect this
}
