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

#include "minishell.h"

t_cmd *create_new_cmd(void)
{
	t_cmd *res;

	res = ft_calloc(sizeof(t_cmd), 1);
	if (!res)
		return (NULL);
	res->argv = NULL;
	res->envp = NULL;
	res->path = NULL;
	res->redirect_in = NULL;
	res->redirect_out = NULL;
	res->redirect_out_mode = none;
	res->here_doc_mode = 0;
	return (res);
}