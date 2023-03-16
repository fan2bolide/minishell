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
#include "minishell.h"

static int get_fd_to_read(int pipes[10240][2], int i, t_cmd cmd);
static int	get_fd_to_write(int	pipes[OPEN_MAX][2], int i, t_list *cmd_lst);
static int	last_cmd(t_list *cmd);

int	execute_cmd_line(t_list *cmd_lst)
{
	int	pipes[OPEN_MAX][2];
	int	pids[OPEN_MAX];
	int fd_to_read;
	int fd_to_write;
	int	i;

	i = 0;
	while (cmd_lst)
	{
		if (!((t_cmd *)cmd_lst->content)->path)
			ft_printf("Turboshell: command not found: %s\n", ((t_cmd *)cmd_lst->content)->argv[0]);

		if (!last_cmd(cmd_lst))
			if (pipe(pipes[i]) < 0)
				return (ft_printf("Failed to create pipes\n"), -1);

		fd_to_read = get_fd_to_read(pipes, i, *((t_cmd *)cmd_lst->content));
		fd_to_write = get_fd_to_write(pipes, i, cmd_lst);
		pids[i] = fork();
		if (pids[i] < 0)
			return (ft_printf("Failed to fork\n"), -1);
		if (pids[i] == 0)
			execute_cmd(*(t_cmd *)cmd_lst->content,\
			fd_to_read,\
			fd_to_write);
		if (is_builtin(((t_cmd *)cmd_lst->content)->argv[0]) >= 0 )
			exec_builtin((t_cmd *)cmd_lst->content,\
			fd_to_read,\
			fd_to_write);
		if (fd_to_read != STDIN_FILENO)
			close(fd_to_read);
		if (fd_to_write != STDOUT_FILENO)
			close(fd_to_write);
		cmd_lst = cmd_lst->next;
		i++;
	}
	return (exit_routine(pipes, pids, i), free_cmd_lst(&cmd_lst), 0);
}

static int get_fd_to_read(int pipes[10240][2], int i, t_cmd cmd)
{
	int res;

	if (cmd.redirect_in)
		res = open_and_get_fd(cmd.redirect_in, O_RDONLY, 0);
	else if (i == 0)
		res = STDIN_FILENO;
	else
		res = (pipes[i - 1][READ]);
	return res;
}

static int	get_fd_to_write(int	pipes[OPEN_MAX][2], int i, t_list *cmd_lst)
{
	int res;
	t_cmd *cmd;

	cmd = (t_cmd *)cmd_lst->content;
	if (cmd->redirect_out)
		res = open_and_get_fd(cmd->redirect_out, O_WRONLY | cmd->redirect_out_mode | O_CREAT, 0644);
	else if (last_cmd(cmd_lst))
		res = STDOUT_FILENO;
	else
		res = (pipes[i][WRITE]);
	return (res);
}

static int	last_cmd(t_list *cmd)
{
	return (cmd->next == NULL);
}
