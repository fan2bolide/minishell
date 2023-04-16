/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:25:43 by alevra            #+#    #+#             */
/*   Updated: 2023/02/08 22:12:59 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

static void	clear_and_exit_with_exit_code(t_cmd_list *const *cmd_list_ptr);
static void	dup2_fds(int to_read, int to_write);
void		heredoc_only_hook(t_cmd *cmd);
void		builtin_hook(t_cmd_list **cmd_list_ptr, const int *fds, \
t_cmd *cmd, const int to_write);
void		check_fds(t_cmd_list **cmd_list_ptr, const int *fds, \
const int to_read, const int to_write);

//'to_read' linked to child 'stdin' and child 'stdout' linked to 'to_write'
void	execute_cmd(t_cmd_list **cmd_list_ptr, int fds[2])
{
	t_cmd		cmd;
	char		**envp;
	const int	to_read = 0;
	const int	to_write = 1;

	check_fds(cmd_list_ptr, fds, to_read, to_write);
	cmd = *(*cmd_list_ptr)->content;
	builtin_hook(cmd_list_ptr, fds, &cmd, to_write);
	heredoc_only_hook(&cmd);
	dup2_fds(fds[to_read], fds[to_write]);
	envp = (char **)ft_keyval_lst_to_str_arr(g_envp_lst);
	ft_lstclear((t_list **)&g_envp_lst, &destroy_keyval);
	if (cmd.path)
		execve(cmd.path, cmd.argv, (char *const *)envp);
	if (envp)
		ft_free_arr((void *)envp, free);
	free(envp);
	ft_lstclear((t_list **)cmd_list_ptr, (void (*)(void *)) & destroy_cmd);
	exit(EXIT_FAILURE);
}

void check_fds(t_cmd_list **cmd_list_ptr, const int *fds, const int to_read, const int to_write)
{
	if (fds[to_read] < 0 || fds[to_write] < 0)
		clear_and_exit_with_exit_code(cmd_list_ptr);
}

//this function is triggered only when th	e command contains a heredoc but doesn't have an exec_name
//(if the function had an exec_name, it would not have a path equal to "heredoc" !)
void heredoc_only_hook(t_cmd *cmd)
{
	if (((*cmd).argv && (*cmd).argv[0] && !*(*cmd).argv[0]) || \
		((*cmd).path && ft_strequ((*cmd).path, "heredoc")))
		exit(EXIT_SUCCESS);
}

void builtin_hook(t_cmd_list **cmd_list_ptr, const int *fds, t_cmd *cmd, const int to_write)
{
	if ((*cmd).argv && is_builtin((*cmd).argv[0]) >= 0)
	{
		exec_builtin(cmd_list_ptr, fds[to_write]);
		clear_and_exit_with_exit_code(cmd_list_ptr);
	}
}

static void	dup2_fds(int to_read, int to_write)
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

static void	clear_and_exit_with_exit_code(t_cmd_list *const *cmd_list_ptr)
{
	int	exit_code;

	exit_code = ft_atoi((const char *)g_envp_lst->content);
	ft_lstclear((t_list **)&g_envp_lst, &destroy_keyval);
	ft_lstclear((t_list **)cmd_list_ptr, (void (*)(void *)) & destroy_cmd);
	exit(exit_code);
}
