/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienlevra <aurelienlevra@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:06:50 by alevra            #+#    #+#             */
/*   Updated: 2023/04/12 02:01:42 by aurelienlev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

void	exit_routine(int pipes[FOPEN_MAX][2], int pids[FOPEN_MAX], int i)
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
	{
		waitpid(pids[k++], &status, 0);
	}
	if (WIFEXITED(status))
		update_exit_code(WEXITSTATUS(status));
}

void	close_pipes(int pipes[FOPEN_MAX][2], int i)
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

void	free_cmd_lst(t_cmd_list **cmd_list)
{
	ft_lstclear((t_list **)cmd_list, (void *)(free_cmd));
}

void	free_cmd(t_cmd *cmd)
{
	free(cmd->path);
	free(cmd->redirect_out);
	free(cmd->redirect_in);
	ft_free_arr((void **)cmd->argv, free);
}

int	open_and_get_fd(char *file, int open_mode, int rights)
{
	if (rights)
		return (open(file, open_mode, rights));
	return (open(file, open_mode));
}