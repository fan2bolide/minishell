/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:14:45 by alevra            #+#    #+#             */
/*   Updated: 2023/04/12 01:55:57 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

static int	get_fd_to_read(int pipes[OPEN_MAX][2], int i, t_cmd cmd);
static int	get_fd_to_write(int pipes[OPEN_MAX][2], int i, \
t_cmd_list *cmd_lst);

void	close_fds(int fds[2], t_cmd_list *cmd_lst)
{
	const int	fd_to_read = 0;
	const int	fd_to_write = 1;

	if (fds[fd_to_read] != STDIN_FILENO)
		close(fds[fd_to_read]);
	if (fds[fd_to_write] != STDOUT_FILENO)
		close(fds[fd_to_write]);
	if (cmd_lst->content->heredoc_mode && \
		cmd_lst->content->heredoc_pipe[READ] != 0)
		close(cmd_lst->content->heredoc_pipe[READ]);
}

void	get_fds(t_cmd_list *cmd_lst, int pipes[10240][2], int i, int fds[2])
{
	const int	fd_to_read = 0;
	const int	fd_to_write = 1;

	fds[fd_to_read] = get_fd_to_read(pipes, i, *(cmd_lst->content));
	fds[fd_to_write] = get_fd_to_write(pipes, i, cmd_lst);
}

static int	get_fd_to_read(int pipes[OPEN_MAX][2], int i, t_cmd cmd)
{
	int	res;

	res = -1;
	if (cmd.redirect_in)
		res = open_and_get_fd(cmd.redirect_in, O_RDONLY, 0);
	else if (cmd.heredoc_mode)
	{
		if (i != 0)
			close(pipes[i - 1][READ]);
		res = cmd.heredoc_pipe[READ];
	}
	else if (i == 0)
		res = STDIN_FILENO;
	else if (i - 1 < OPEN_MAX)
		res = (pipes[i - 1][READ]);
	return (res);
}

static int	get_fd_to_write(int pipes[OPEN_MAX][2], int i, t_cmd_list *cmd_lst)
{
	int		res;
	t_cmd	*cmd;

	res = -1;
	cmd = cmd_lst->content;
	if (cmd->redirect_out)
	{
		res = open_and_get_fd(cmd->redirect_out, \
		O_WRONLY | cmd->redirect_out_mode | O_CREAT, 0644);
		if (pipes[i][WRITE] > STDERR_FILENO)
			close(pipes[i][WRITE]);
	}
	else if (is_last_cmd(cmd_lst))
		res = STDOUT_FILENO;
	else if (i < OPEN_MAX)
		res = (pipes[i][WRITE]);
	return (res);
}
