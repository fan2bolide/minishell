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
static int	token_cmd_line_size(t_list *token_lst);
void	log_to_exec(t_to_exec *to_exec);
void		case_current_token_type_is_exec_name(
		t_list *token_lst_cursor, t_to_exec *to_exec);

//debug
void	log_to_exec_lst(t_list *to_exec_list)
{
	t_to_exec	*current_to_exec;

	if (!to_exec_list)
		return (ft_printf("log_to_exec_lst failed (NULL pointer)\n"), (void)0);
	current_to_exec = to_exec_list->content;
	log_to_exec(current_to_exec);
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
	current_to_exec = to_exec_lst->content;
	current_to_exec = malloc(sizeof(t_to_exec));
	while (current_token->type != operator_pipe)
	{
		switch_case(token_lst_cursor, current_to_exec);
		token_lst_cursor = token_lst_cursor->next;
		current_token = token_lst_cursor->content;
	}
	ft_printf("logging to_exec_lst : \n"); //debug
	log_to_exec_lst(to_exec_lst);
	// current_to_exec->content;
	// current_token = current_token->next;
	// current_to_exec =
}

static void	switch_case(t_list *token_lst_cursor, t_to_exec *to_exec)
{
	t_token	*current_token;

	current_token = token_lst_cursor->content;
	ft_printf("Current token :\n"); //debug
	print_token(current_token);
	if (current_token->type == exec_name)
		case_current_token_type_is_exec_name(token_lst_cursor, to_exec);
	else
		ft_printf("another case\n");//debug
}

void		case_current_token_type_is_exec_name(
	t_list *token_lst_cursor, t_to_exec *to_exec)
{
	int		cmd_tab_size;
	t_token	*current_token;
	int		i;

	ft_printf("case \"current_token->type == exec_name\"\n"); //debug
	i = 0;
	cmd_tab_size = token_cmd_line_size(token_lst_cursor) + 1;
	to_exec->cmd = ft_calloc(cmd_tab_size, sizeof(char *));
	while (cmd_tab_size > 2) //unexplained magic number here,
		// surely a bug is hidden causing to_exec not to be fully assigned
		{
			to_exec->cmd[i++] = current_token->content;
			ft_printf("to_exec->cmd[%d] : %s\n",i - 1, to_exec->cmd[i - 1]); //debug
			token_lst_cursor = token_lst_cursor->next;
			current_token = token_lst_cursor->content;
			cmd_tab_size--;
		}
}

// for a cmd line given into a token format,
// returns 1(for the cmd) + the number of args following the cmd
static int	token_cmd_line_size(t_list *token_lst)
{
	int	res;

	res = 0;
	if (((t_token *)token_lst->content)->type != exec_name)
		return (0);
	res++;
	token_lst = token_lst->next;
	while (((t_token *)token_lst->content)->type == arg)
	{
		res++;
		token_lst = token_lst->next;
	}
	return (res);
}
