/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 22:37:14 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/14 22:37:15 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///updates the env '?' variable with the exit code of the last program called
void	update_exit_code(int exit_code)
{
	char	*new_exit_code;

	new_exit_code = ft_itoa(exit_code);
	free(g_envp_lst->content->value);
	g_envp_lst->content->value = new_exit_code;
}

/// sets the value of env's '?' variable to 0
/// \return 1 if allocation fails, 0 else
bool	set_exit_code(void)
{
	t_keyval_list	*new;

	new = malloc(sizeof(t_keyval_list));
	if (!new)
		return (false);
	new->next = g_envp_lst;
	new->content = malloc(sizeof(t_keyval));
	if (!new->content)
		return (free(new), false);
	new->content->key = ft_strdup("?");
	new->content->value = ft_strdup("0");
	if (!new->content->key || !new->content->value)
	{
		free(new->content->key);
		free(new->content->value);
		free(new);
		return (false);
	}
	g_envp_lst = new;
	return (true);
}

/// \return the value of env's '?' variable
int	get_exit_code(void)
{
	return (ft_atoi(g_envp_lst->content->value));
}
