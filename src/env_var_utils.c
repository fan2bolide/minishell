/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 23:33:32 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	env_var_exist(t_keyval *keyval_to_check);
static	void	insert_env_var(t_keyval *keyval_to_insert);

/**
 * insert env_var in ascii order
 * if env_var already exist,
	update the value and free the keyval given in parameter
 * @param keyval_to_insert
 */
void	insert_or_update_env_var(t_keyval *keyval_to_insert)
{
	if (!keyval_to_insert)
		return ;
	if (env_var_exist(keyval_to_insert))
		update_env_var(keyval_to_insert);
	else
		insert_env_var(keyval_to_insert);
}

static bool	env_var_exist(t_keyval *keyval_to_check)
{
	t_keyval_list	*curr;

	if (g_envp_lst)
		curr = g_envp_lst->next;
	if (!g_envp_lst || !curr)
		return (0);
	while (curr && !ft_strequ(keyval_to_check->key, curr->content->key))
		curr = curr->next;
	if (!curr)
		return (0);
	return (1);
}

void	update_env_var(t_keyval *keyval_to_update)
{
	t_keyval_list	*curr;

	if (g_envp_lst)
		curr = g_envp_lst->next;
	if (!g_envp_lst || !curr)
		return ;
	while (!ft_strequ(keyval_to_update->key, curr->content->key))
		curr = curr->next;
	if (keyval_to_update->value)
	{
		free(curr->content->value);
		curr->content->value = ft_strdup(keyval_to_update->value);
		if (!curr->content->value)
			print_error(alloc_error, "update_env_var");
	}
	destroy_keyval(keyval_to_update);
}

static void	insert_env_var(t_keyval *keyval_to_insert)
{
	t_keyval_list	*curr;
	t_keyval_list	*tmp;

	curr = NULL;
	if (g_envp_lst)
		curr = g_envp_lst->next;
	if (!curr || !g_envp_lst)
		return (print_error(alloc_error, "insert_env_var"), (void)0);
	while (curr->next && ft_strcmp(keyval_to_insert->key, \
			curr->next->content->key) > 0)
		(curr) = (curr)->next;
	tmp = curr->next;
	curr->next = (t_keyval_list *)ft_lstnew(keyval_to_insert);
	curr->next->next = tmp;
}
