/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 04:14:38 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/11 04:14:47 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_there_an_exec_name_between_pipes(int is_exec_name, \
												const t_token_list *curr)
{
	if (((t_token *)curr->content)->type == operator_pipe)
		is_exec_name = 0;
	if (((t_token *)curr->content)->type == exec_name)
		is_exec_name = 1;
	return (is_exec_name);
}

static t_token_list	*get_end_of_list(char *command_line, size_t i, \
							t_token_list *list)
{
	t_token_list	*curr;
	t_token			*token;
	int				is_exec_name;

	is_exec_name = 0;
	curr = list;
	while (command_line[i])
	{
		is_exec_name = is_there_an_exec_name_between_pipes(is_exec_name, curr);
		token = evaluate_expression(command_line + i, \
		curr->content, is_exec_name);
		curr->next = (t_token_list *)ft_lstnew(token);
		if (!curr->next || !curr->next->content)
			return (print_error(alloc_error, "lexer"), \
					ft_lstclear((t_list **)&list, destroy_token), NULL);
		is_exec_name = is_there_an_exec_name_between_pipes(is_exec_name, curr);
		curr = curr->next;
		if (get_next_expression(command_line + i) == 0)
			return (print_error(parsing_error, command_line + i), \
					ft_lstclear((t_list **)&list, destroy_token), NULL);
		i += get_next_expression(command_line + i);
	}
	return (list);
}

t_token_list	*get_main_token_list(char *command_line)
{
	size_t			i;
	t_token_list	*list;
	t_token			*token;

	if (!command_line || !*command_line)
		return (NULL);
	token = evaluate_expression(command_line, NULL, 0);
	list = (t_token_list *)ft_lstnew(token);
	if (!list || !token)
		return (print_error(alloc_error, "lexer"), \
				ft_lstclear((t_list **)&list, destroy_token), NULL);
	i = get_next_expression(command_line);
	return (get_end_of_list(command_line, i, list));
}
