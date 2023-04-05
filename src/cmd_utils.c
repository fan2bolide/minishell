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

t_cmd *create_new_cmd()
{
	t_cmd *res;

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
	return (res);
}

void destroy_cmd(t_cmd *cmd)
{
	free(cmd->path);
	if (cmd->argv)
		ft_old_split_destroy(cmd->argv);
	free(cmd->redirect_out);
	free(cmd->heredoc_delim);
	free(cmd->redirect_in);
	free(cmd);
}