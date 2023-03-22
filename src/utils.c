/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:06:50 by alevra            #+#    #+#             */
/*   Updated: 2023/02/23 15:25:36 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

void	ft_free_arr(void ** array, void (*del)(void *)); // might want to move this into baj libft

void	exit_routine(int pipes[OPEN_MAX][2], int pids[OPEN_MAX],
		int i)
{
	close_pipes(pipes, i);
	wait_all_child_proc(pids, i);
}

void	wait_all_child_proc(int *pids, int childs_counter)
{
	int	k;

	k = 0;
	while (k < childs_counter)
	{
		waitpid(pids[k++], NULL, 0);
	}
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

void	free_cmd_lst(t_cmdlist **cmd_list)
{
	ft_lstclear((t_list **)cmd_list, (void *)(free_cmd));
}

void	free_cmd(t_cmd *cmd)
{
	free(cmd->path);
	free(cmd->redirect_out);
	free(cmd->redirect_in);

	ft_free_arr((void **) cmd->envp_lst_ptr, free);
	ft_free_arr((void **) cmd->argv, free);

}

//last element of array must be a NULL pointer
void	ft_free_arr(void ** array, void (*del)(void *))
{
	int	i;

	i = 0;
	while(array[i])
		del(array[i++]);
}

int open_and_get_fd(char *file, int open_mode, int rights)
{
	if (rights)
		return (open(file,open_mode, rights));
	return (open(file,open_mode));
}