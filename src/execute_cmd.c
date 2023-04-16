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
