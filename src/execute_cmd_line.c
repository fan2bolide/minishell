/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_all_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:14:45 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 18:41:04 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

static void	case_first(t_cmd *cmd, int pipes[OPEN_MAX][2], int i,
						  int fd_file_1);
static void	case_middle(t_cmd *cmd, int pipes[OPEN_MAX][2], int i);
static void	case_last(t_cmd *cmd, int pipes[OPEN_MAX][2], int i,
						 int fd_file_2);
static void	switch_case(t_list *cmd_lst, int pipes[OPEN_MAX][2], int i,
						   int files[2]);

int	execute_all_cmds(t_list *cmd_lst, int files[2])
{
	int	pipes[OPEN_MAX][2];
	int	pids[OPEN_MAX];
	int	i;

	i = 0;
	while (cmd_lst)
	{
		if (!((t_cmd *)cmd_lst)->path)
			ft_printf("command not found: %s\n", ((t_cmd *)cmd_lst)->argv[0]);
		if (pipe(pipes[i]) < 0)
			return (ft_printf("Failed to create pipes\n"), -1);
		pids[i] = fork();
		if (pids[i] < 0)
			return (ft_printf("Failed to fork\n"), -1);
		if (pids[i] == 0)
			switch_case(cmd_lst, pipes, i, files);
		if (close(pipes[i][WRITE]) < 0)
		{
			ft_printf("Failed to close pipe %d\n", i);
			return (exit_routine(pipes, files, pids, i), free_cmd_tab(&cmd_lst),
				-1);
		}
		i++;
	}
	return (exit_routine(pipes, files, pids, i), free_cmd_tab(&cmd_lst), 0);
}

static void	switch_case(t_list *cmd_lst, int pipes[OPEN_MAX][2], int i,
						   int files[2])
{
	if (i == 0)
		return (case_first( (t_cmd *)cmd_lst->content , pipes, i, files[FILE_1]));
	if (!cmd_lst->next)
		return (case_last(cmd_lst->content, pipes, i, files[FILE_2]));
	return (case_middle(cmd_lst->content, pipes, i));
}

static void	case_first(t_cmd *cmd, int pipes[OPEN_MAX][2], int i,
						  int fd_file_1)
{
	close(pipes[i][READ]);
	if (cmd->here_doc_mode)
		manage_here_doc(*cmd, pipes, i, fd_file_1);
	if (fd_file_1 > 0 && cmd->path)
		execute_cmd(*cmd, fd_file_1, pipes[i][WRITE]);
	close(pipes[i][WRITE]);
	exit(EXIT_FAILURE);
}

static void	case_middle(t_cmd *cmd, int pipes[OPEN_MAX][2], int i)
{
	if (close(pipes[i - 1][WRITE]) < 0)
	{
		ft_printf("Failed to close some pipes\n");
		exit(EXIT_FAILURE);
	}
	if (cmd->path)
		execute_cmd(*cmd, pipes[i - 1][READ], pipes[i][WRITE]);
	close(pipes[i - 1][READ]);
	close(pipes[i][WRITE]);
	exit(EXIT_FAILURE);
}

static void	case_last(t_cmd *cmd, int pipes[OPEN_MAX][2], int i,
						 int fd_file_2)
{
	if (close(pipes[i][WRITE]) < 0)
	{
		ft_printf("Failed to close some pipes\n");
		exit(EXIT_FAILURE);
	}
	close(pipes[i - 1][WRITE]);
	if (fd_file_2 > 0)
		execute_cmd(*cmd, pipes[i - 1][READ], fd_file_2);
	close(pipes[i - 1][READ]);
	close(fd_file_2);
	exit(EXIT_FAILURE);
}
