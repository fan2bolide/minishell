/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 23:33:32 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	env(int to_write)
{
	t_keyval_list	*curr;

	curr = g_envp_lst;
	if (curr)
		curr = curr->next;
	while (curr && curr->content)
	{
		if (curr->content->value)
		{
			ft_putstr_fd(curr->content->key, to_write);
			ft_putstr_fd("=", to_write);
			ft_putstr_fd(curr->content->value, to_write);
			ft_putstr_fd("\n", to_write);
		}
		curr = curr->next;
	}
}
