/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyval_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 23:33:32 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

static int	fill_array(t_keyval_list *lst, void **arr);

void	**ft_keyval_lst_to_str_arr(t_keyval_list *lst)
{
	size_t	arr_size;
	void	**arr;

	arr_size = ft_lstsize((t_list *)lst);
	arr = ft_calloc(arr_size + 1, sizeof(char *));
	if (!arr)
		return (print_error(alloc_error, "(keyval to str arr)"), NULL);
	if (fill_array(lst, arr) < 0)
		return (NULL);
	return (arr);
}

static int	fill_array(t_keyval_list *lst, void **arr)
{
	int		i;
	char	*to_destroy;

	i = 0;
	while (lst)
	{
		if (lst->content && lst->content->key && lst->content->value)
		{
			to_destroy = ft_strjoin_secure(lst->content->key, "=");
			arr[i] = ft_strjoin_secure(to_destroy, lst->content->value);
			free(to_destroy);
			if (!arr[i])
			{
				print_error(alloc_error, "ft_keyval_lst_to_str_arr");
				ft_free_arr(arr, free);
				free(arr);
				return (-1);
			}
			i++;
		}
		lst = lst->next;
	}
	arr[i] = NULL;
	return (0);
}

/**
 * create a new "keyval"
 *  var must be something like --> abc=value
 * strdup whats before the first equal sign to the key element
 * strdup whats after the first equal sign to the value element
 * @param var
 * @return a new keyval
 */
t_keyval	*create_keyval_from_env_var(char *var)
{
	t_keyval	*res;
	char		*equal;

	if (!var)
		return (NULL);
	res = create_keyval();
	if (!res)
		return (NULL);
	equal = ft_strchr(var, '=');
	if (!equal)
	{
		res->key = ft_strdup(var);
		res->value = NULL;
		return (res);
	}
	res->key = ft_strndup(var, equal - var);
	res->value = NULL;
	if (*(equal + 1))
		res->value = ft_strdup(equal + 1);
	return (res);
}

void	destroy_keyval(void *keyval)
{
	if (keyval)
	{
		free(((t_keyval *)keyval)->value);
		free(((t_keyval *)keyval)->key);
	}
	free(keyval);
}

t_keyval	*create_keyval(void)
{
	t_keyval	*res;

	res = malloc(sizeof(t_keyval));
	if (!res)
		return (ft_putstr_fd("an error occurred (create_keyval..)\n", 2), NULL);
	res->value = NULL;
	res->key = NULL;
	return (res);
}
