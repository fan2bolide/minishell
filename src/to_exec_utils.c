/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 23:33:32 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_to_exec *create_new_to_exec(void)
{
	t_to_exec *res;

	res = ft_calloc(sizeof(t_to_exec), 1);
	if (!res)
		return (NULL);
	res->cmd = NULL;
	res->envp = NULL;
	res->path = NULL;
	res->redirect_in = NULL;
	res->redirect_out = NULL;
	res->redirect_out_mode = none;
	res->here_doc_mode = 0;
	return (res);
}