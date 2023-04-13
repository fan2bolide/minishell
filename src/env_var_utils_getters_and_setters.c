/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils_getters_and_setters.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 23:33:32 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/**
 * DO NOT FREE THE RETURN VALUE
 * @param var_name
 * @return value of the variable <varname> in environment
 */
char	*get_env_var_value(char *var_name)
{
	t_keyval_list	*curr;

	curr = g_envp_lst;
	if (!var_name || !g_envp_lst || curr->content)
		return (NULL);
	while (curr && !ft_strequ(curr->content->key, var_name))
		curr = curr->next;
	if (!curr)
		return (NULL);
	return (curr->content->value);
}

/**
 * @param var_name
 * @return keyval of <varname> in environment
 */
t_keyval	*get_env_var(char *var_name)
{
	t_keyval_list	*curr;

	curr = g_envp_lst;
	if (!var_name || !g_envp_lst)
		return (NULL);
	while (curr && !ft_strequ(curr->content->key, var_name))
		curr = curr->next;
	if (!curr)
		return (NULL);
	return (curr->content);
}

/**
 * @param var_name
 */
void	set_env_var_value(char *var_key, char *var_value)
{
	t_keyval	*var_to_set;

	if (!var_key)
		return (print_error(error_occured, "set_env_var_value"));
	var_to_set = get_env_var(var_key);
	if (var_to_set)
		free(var_to_set->value);
	if (!var_to_set)
	{
		var_to_set = create_keyval();
		var_to_set->key = ft_strdup(var_key);
		insert_or_update_env_var(var_to_set);
	}
	var_to_set->value = ft_strdup(var_value);
	if (!var_to_set->value)
		print_error(error_occured, "set_env_var_value");
}
