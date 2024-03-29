/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 23:33:32 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

t_cmd	*create_new_cmd(void)
{
	t_cmd	*res;

	res = ft_calloc(sizeof(t_cmd), 1);
	if (!res)
		return (NULL);
	res->argv = NULL;
	res->path = NULL;
	res->redirect_in = NULL;
	res->redirect_out = NULL;
	res->redirect_out_mode = 0;
	res->heredoc_mode = 0;
	res->heredoc_delim = NULL;
	res->error = false;
	res->abort_cmd_line = false;
	return (res);
}

void	destroy_cmd(t_cmd *cmd)
{
	free_cmd(cmd);
	free(cmd);
}

void	free_cmd_lst(t_cmd_list **cmd_list)
{
	ft_lstclear((t_list **)cmd_list, (void *)(free_cmd));
}

void	free_cmd(t_cmd *cmd)
{
	free(cmd->path);
	if (cmd->argv)
		ft_free_arr((void **)cmd->argv, free);
	free(cmd->argv);
	free(cmd->redirect_out);
	free(cmd->heredoc_delim);
	free(cmd->redirect_in);
}
