/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_all_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:14:45 by alevra            #+#    #+#             */
/*   Updated: 2023/02/16 19:44:50 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	case_first(t_to_exec to_exec, int pipes[OPEN_MAX][2], int i,
				int fd_file_1);
static void	case_middle(t_to_exec to_exec, int pipes[OPEN_MAX][2], int i);
static void	case_last(t_to_exec to_exec, int pipes[OPEN_MAX][2], int i,
				int fd_file_2);
static void	switch_case(t_to_exec *cmds, int pipes[OPEN_MAX][2], int i,
				int files[2]);

int	execute_all_cmds(t_to_exec *cmds, int files[2])
{
	int	pipes[OPEN_MAX][2];
	int	pids[OPEN_MAX];
	int	i;

	i = 0;
	while (cmds[i].cmd)
	{
		if (!cmds[i].path)
			ft_printf("command not found: %s\n", cmds[i].cmd[0]);
		if (pipe(pipes[i]) < 0)
			return (ft_printf("Failed to create pipes\n"), -1);
		pids[i] = fork();
		if (pids[i] < 0)
			return (ft_printf("Failed to fork\n"), -1);
		if (pids[i] == 0)
			switch_case(cmds, pipes, i, files);
		if (close(pipes[i][WRITE]) < 0)
		{
			ft_printf("Failed to close pipe %d\n", i);
			return (exit_routine(pipes, files, pids, i), free_cmd_tab(&cmds),
				-1);
		}
		i++;
	}
	return (exit_routine(pipes, files, pids, i), free_cmd_tab(&cmds), 0);
}

static void	switch_case(t_to_exec *cmds, int pipes[OPEN_MAX][2], int i,
		int files[2])
{
	if (i == 0)
		return (case_first(cmds[i], pipes, i, files[FILE_1]));
	if (i != 0 && cmds[i + 1].cmd)
		return (case_middle(cmds[i], pipes, i));
	if (!cmds[i + 1].cmd)
		return (case_last(cmds[i], pipes, i, files[FILE_2]));
}

static void	case_first(t_to_exec to_exec, int pipes[OPEN_MAX][2], int i,
		int fd_file_1)
{
	close(pipes[i][READ]);
	if (i == 0 && BONUS && ft_strequ(to_exec.cmd[0], "here_doc"))
		manage_here_doc(to_exec, pipes, i, fd_file_1);
	if (fd_file_1 > 0 && to_exec.path)
		execute_cmd(to_exec, fd_file_1, pipes[i][WRITE]);
	close(pipes[i][WRITE]);
	exit(EXIT_FAILURE);
}

static void	case_middle(t_to_exec to_exec, int pipes[OPEN_MAX][2], int i)
{
	if (close(pipes[i - 1][WRITE]) < 0)
	{
		ft_printf("Failed to close some pipes\n");
		exit(EXIT_FAILURE);
	}
	if (to_exec.path)
		execute_cmd(to_exec, pipes[i - 1][READ], pipes[i][WRITE]);
	close(pipes[i - 1][READ]);
	close(pipes[i][WRITE]);
	exit(EXIT_FAILURE);
}

static void	case_last(t_to_exec to_exec, int pipes[OPEN_MAX][2], int i,
		int fd_file_2)
{
	if (close(pipes[i][WRITE]) < 0)
	{
		ft_printf("Failed to close some pipes\n");
		exit(EXIT_FAILURE);
	}
	close(pipes[i - 1][WRITE]);
	if (fd_file_2 > 0)
		execute_cmd(to_exec, pipes[i - 1][READ], fd_file_2);
	close(pipes[i - 1][READ]);
	close(fd_file_2);
	exit(EXIT_FAILURE);
}
