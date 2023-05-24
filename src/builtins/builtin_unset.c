/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 23:33:32 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	unset(char *var_to_unset)
{
	t_keyval_list	*curr;
	t_keyval_list	*tmp;

	if (!var_to_unset)
		return ((void)0);
	curr = g_envp_lst;
	if (ft_strequ(curr->content->key, var_to_unset))
	{
		g_envp_lst = g_envp_lst->next;
		ft_lstdelone((t_list *)curr, (void (*)(void *)) & destroy_keyval);
		return ;
	}
	while (curr && curr->next && \
			!ft_strequ(curr->next->content->key, var_to_unset))
		curr = curr->next;
	if (curr->next)
	{
		tmp = curr->next->next;
		ft_lstdelone((t_list *)curr->next, & destroy_keyval);
		curr->next = tmp;
	}
}
