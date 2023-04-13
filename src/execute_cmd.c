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
#include "minishell.h"

//'to_read' linked to child 'stdin' and child 'stdout' linked to 'to_write'
void	execute_cmd(t_cmd_list **cmd_list_ptr, int to_read, int to_write)
{
	t_cmd	cmd;
	char	**envp;

	if (to_read < 0 || to_write < 0)
	{
		update_exit_code(1);
		return (print_error(error_occured, "negative file descriptors"));
	}
	cmd = *(*cmd_list_ptr)->content;
	if (cmd.argv && is_builtin(cmd.argv[0]) >= 0)
	{
		exec_builtin(cmd_list_ptr, to_write);
		exit(ft_atoi((const char *)g_envp_lst->content));
	}
	if ((cmd.argv && cmd.argv[0] && !*cmd.argv[0]) || \
		(cmd.path && ft_strequ(cmd.path, "heredoc")))
		exit(EXIT_SUCCESS);
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
