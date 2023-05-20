/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <aurelienlevra@student.42           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:06:50 by alevra            #+#    #+#             */
/*   Updated: 2023/04/12 02:01:42 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

void	exit_routine(int pipes[OPEN_MAX][2], int pids[OPEN_MAX], int i)
{
	close_pipes(pipes, i);
	wait_all_child_proc(pids, i);
}

void	wait_all_child_proc(int *pids, int childs_counter)
{
	int	k;
	int	status;

	k = 0;
	while (k < childs_counter)
		waitpid(pids[k++], &status, 0);
	if (WIFEXITED(status))
		update_exit_code(WEXITSTATUS(status));
}

void	close_pipes(int pipes[OPEN_MAX][2], int i)
{
	int	k;

	k = 0;
	while (k < i)
	{
		if (pipes[k][READ] != STDIN_FILENO)
			close(pipes[k][READ]);
		if (pipes[k][WRITE] != STDOUT_FILENO && pipes[k][WRITE] != STDIN_FILENO)
			close(pipes[k][WRITE]);
		k++;
	}
}

int	open_and_get_fd(char *file, int open_mode, int rights)
{
	int	res;

	if (rights)
		res = (open(file, open_mode, rights));
	else
		res = (open(file, open_mode));
	if (res < 0)
	{
		perror(file);
		update_exit_code(1);
	}
	return (res);
}
