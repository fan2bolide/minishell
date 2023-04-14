/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:14:45 by alevra            #+#    #+#             */
/*   Updated: 2023/04/12 01:55:57 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

int	execute_cmd_line(t_cmd_list *cmd_lst)
{
	int			pipes[OPEN_MAX][2];
	int			pids[OPEN_MAX];
	int			fds[2];
	int			i;

	i = 0;
	ft_memset(pipes, 0, sizeof(int) * OPEN_MAX * 2);
	while (cmd_lst)
	{
		check_path(cmd_lst);
		if (!create_and_check_pipes(pipes, i, cmd_lst))
			return (0);
		get_fds(cmd_lst, pipes, i, fds);
		if (check_if_single_builtin(&cmd_lst, fds))
			return (1);
		pids[i] = fork();
		if (pids[i] < 0)
			return (printf("Failed to fork\n"), 0);
		if (pids[i] == 0)
			execute_cmd(&cmd_lst, fds);
		close_fds(fds, cmd_lst);
		cmd_lst = destroy_first_cmd_lst(cmd_lst);
		i++;
	}
	return (exit_routine(pipes, pids, i), free_cmd_lst(&cmd_lst), 1);
}
