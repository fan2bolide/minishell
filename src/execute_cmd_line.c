/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:14:45 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 18:41:04 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

static int get_fd_to_read(int pipes[10240][2], int i, t_cmd cmd);
static int	get_fd_to_write(int	pipes[OPEN_MAX][2], int i, t_cmdlist *cmd_lst);
static int	is_last_cmd(t_cmdlist *cmd);
void check_path(const t_cmdlist *cmd_lst);
int create_and_check_pipes(const int pipes[10240][2], int i);
void get_fds(t_cmdlist *cmd_lst, int pipes[10240][2], int i, int *fd_to_read, int *fd_to_write);

void close_fds(int fd_to_read, int fd_to_write);

int	execute_cmd_line(t_cmdlist *cmd_lst)
{
	int	pipes[OPEN_MAX][2];
	int	pids[OPEN_MAX];
	int fd_to_read;
	int fd_to_write;
	int	i;

	i = 0;
	while (cmd_lst)
	{
		check_path(cmd_lst);
		if (!is_last_cmd(cmd_lst))
			if (!create_and_check_pipes(pipes, i))
				return (0);
		get_fds(cmd_lst, pipes, i, &fd_to_read, &fd_to_write);
		pids[i] = fork();
		if (pids[i] < 0)
			return (ft_printf("Failed to fork\n"), 0);
		if (pids[i] == 0)
			execute_cmd(*cmd_lst->content,\
			fd_to_read,\
			fd_to_write);
		if (!cmd_lst->content->heredoc_mode && is_builtin((cmd_lst->content)->argv[0]) >= 0 ) // ici aussi ?
			exec_builtin(cmd_lst->content,\
			fd_to_read,\
			fd_to_write);
		close_fds(fd_to_read, fd_to_write);
		if ((cmd_lst->content)->heredoc_mode)
			close((cmd_lst->content)->heredoc_pipe[READ]);
		cmd_lst = cmd_lst->next;
		i++;
	}
	return (exit_routine(pipes, pids, i), free_cmd_lst(&cmd_lst), 1);
}

void close_fds(int fd_to_read, int fd_to_write) {
	if (fd_to_read != STDIN_FILENO)
		close(fd_to_read);
	if (fd_to_write != STDOUT_FILENO)
		close(fd_to_write);
}

void get_fds(t_cmdlist *cmd_lst, int pipes[10240][2], int i, int *fd_to_read, int *fd_to_write) {
	(*fd_to_read) = get_fd_to_read(pipes, i, *(cmd_lst->content));
	(*fd_to_write) = get_fd_to_write(pipes, i, cmd_lst);
}

static int get_fd_to_read(int pipes[10240][2], int i, t_cmd cmd)
{
	int res;

	if (cmd.redirect_in)
		res = open_and_get_fd(cmd.redirect_in, O_RDONLY, 0);
	else if (cmd.heredoc_mode)
	{
		if (i != 0)
			close (pipes[i - 1][READ]);
		res = cmd.heredoc_pipe[READ];
	}
	else if (i == 0)
		res = STDIN_FILENO;
	else
		res = (pipes[i - 1][READ]);
	return res;
}

static int	get_fd_to_write(int	pipes[OPEN_MAX][2], int i, t_cmdlist *cmd_lst)
{
	int res;
	t_cmd *cmd;

	cmd = cmd_lst->content;
	if (cmd->redirect_out)
		res = open_and_get_fd(cmd->redirect_out, O_WRONLY | cmd->redirect_out_mode | O_CREAT, 0644);
	else if (is_last_cmd(cmd_lst))
		res = STDOUT_FILENO;
	else
		res = (pipes[i][WRITE]);
	return (res);
}

static int	is_last_cmd(t_cmdlist *cmd)
{
	return (cmd->next == NULL);
}

void check_path(const t_cmdlist *cmd_lst) {
	if (!(cmd_lst->content)->path)
		ft_printf("Turboshell: command not found: %s\n", (cmd_lst->content)->argv[0]); //TODO SEGFAULT ICI
}

int create_and_check_pipes(const int pipes[10240][2], int i) {
	if (pipe(pipes[i]) < 0)
		return (ft_printf("Failed to create pipes\n"), 0);
	return (1);
}

