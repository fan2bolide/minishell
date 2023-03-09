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

static int	get_fd_to_read(int	pipes[OPEN_MAX][2], int i);
static int	get_fd_to_write(int	pipes[OPEN_MAX][2], int i, t_list *next_cmd);
int	execute_cmd_line(t_list *cmd_lst )
{
	int	pipes[OPEN_MAX][2];
	int	pids[OPEN_MAX];
	int	i;

	i = 0;
	while (cmd_lst)
	{
		if (!((t_cmd *)cmd_lst->content)->path)
			ft_printf("command not found: %s\n", ((t_cmd *)cmd_lst)->argv[0]);
		if (pipe(pipes[i]) < 0)
			return (ft_printf("Failed to create pipes\n"), -1);
		pids[i] = fork();
		if (pids[i] < 0)
			return (ft_printf("Failed to fork\n"), -1);
		if (pids[i] == 0)
			execute_cmd(*(t_cmd *)cmd_lst->content,\
			get_fd_to_read(pipes, i),\
			get_fd_to_write(pipes, i , cmd_lst->next));
		if (close(pipes[i][WRITE]) < 0 || close(pipes[i - (i > 0)][READ]))
		{
			ft_printf("Failed to close pipe %d\n", i);
			return (exit_routine(pipes, pids, i), free_cmd_lst(&cmd_lst), -1);
		}
		cmd_lst = cmd_lst->next;
		i++;
	}
	return (exit_routine(pipes, pids, i), free_cmd_lst(&cmd_lst), 0);
}

static int	get_fd_to_read(int	pipes[OPEN_MAX][2], int i)
{
	if (i > 0)
		return pipes[i - 1][READ];
	return (pipes[0][READ]);
}

static int	get_fd_to_write(int	pipes[OPEN_MAX][2], int i, t_list *next_cmd)
{
	int res;
	int is_last_cmd;
	is_last_cmd = (next_cmd == NULL);

	if (is_last_cmd)
		res = (STDOUT_FILENO);
	else
		res = (pipes[i][WRITE]);
	return (res);
}
