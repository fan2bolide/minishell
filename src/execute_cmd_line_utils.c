/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:14:45 by alevra            #+#    #+#             */
/*   Updated: 2023/04/12 01:55:57 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

static bool			is_single_builtin_cmd(t_cmd_list *cmd_lst);

int	check_if_single_builtin(t_cmd_list **cmd_lst, const int *fds)
{
	const int	fd_to_write = 1;

	if (is_single_builtin_cmd((*cmd_lst)))
	{
		exec_builtin(cmd_lst, fds[fd_to_write]);
		(*cmd_lst) = destroy_first_cmd_lst((*cmd_lst));
		return (1);
	}
	return (0);
}

t_cmd_list	*destroy_first_cmd_lst(t_cmd_list *cmd_lst)
{
	t_cmd_list	*new_cmd_list;

	new_cmd_list = cmd_lst->next;
	ft_lstdelone((t_list *)cmd_lst, (void (*)(void *))destroy_cmd);
	return (new_cmd_list);
}

static bool	is_single_builtin_cmd(t_cmd_list *cmd_lst)
{
	if (!cmd_lst->next)
		if (cmd_lst->content->argv)
			if (is_builtin(cmd_lst->content->argv[0]) >= 0)
				return (true);
	return (false);
}

int	is_last_cmd(t_cmd_list *cmd)
{
	return (cmd->next == NULL);
}

int	create_and_check_pipes(int pipes[10240][2], int i, t_cmd_list *cmd_lst)
{
	if (is_last_cmd(cmd_lst))
		return (1);
	if (pipe(pipes[i]) < 0)
		return (print_error(error_occured, "Failed to create pipes\n"), 0);
	return (1);
}
