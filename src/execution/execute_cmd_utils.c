/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:14:45 by alevra            #+#    #+#             */
/*   Updated: 2023/04/12 01:55:57 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

static void	clear_and_exit_with_exit_code(t_cmd_list *const *cmd_list_ptr);

//this function is triggered only
// when the command contains a heredoc but doesn't have an exec_name
//(if the function had an exec_name,
// it would not have a path equal to "heredoc" !)
void	heredoc_only_hook(t_cmd *cmd)
{
	if (((*cmd).argv && (*cmd).argv[0] && !*(*cmd).argv[0]) || \
		((*cmd).path && ft_strequ((*cmd).path, "heredoc")))
		exit(EXIT_SUCCESS);
}

void	builtin_hook(t_cmd_list **cmd_list_ptr, const int *fds, t_cmd *cmd, \
const int to_write)
{
	if ((*cmd).argv && is_builtin((*cmd).argv[0]) >= 0)
	{
		exec_builtin(cmd_list_ptr, fds[to_write]);
		clear_and_exit_with_exit_code(cmd_list_ptr);
	}
}

void	clear_and_exit_with_exit_code(t_cmd_list *const *cmd_list_ptr)
{
	int	exit_code;

	exit_code = ft_atoi((const char *)g_envp_lst->content);
	ft_lstclear((t_list **)&g_envp_lst, &destroy_keyval);
	ft_lstclear((t_list **)cmd_list_ptr, (void (*)(void *)) & destroy_cmd);
	exit(exit_code);
}

void	check_fds(t_cmd_list **cmd_list_ptr, const int *fds, \
const int to_read, const int to_write)
{
	if (fds[to_read] < 0 || fds[to_write] < 0)
		clear_and_exit_with_exit_code(cmd_list_ptr);
}

void	dup2_fds(int to_read, int to_write)
{
	if (to_read != STDIN_FILENO)
	{
		dup2(to_read, STDIN_FILENO);
		close(to_read);
	}
	if (to_write != STDOUT_FILENO)
	{
		dup2(to_write, STDOUT_FILENO);
		close(to_write);
	}
}
