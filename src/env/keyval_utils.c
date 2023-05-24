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

static t_keyval	*append_keyval(char *var, t_keyval *res, const char *equal);

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
	bool		append;

	append = 0;
	if (!var)
		return (NULL);
	res = create_keyval();
	if (!res)
		return (NULL);
	equal = ft_strchr(var, '=');
	if (!equal)
		return (res->key = ft_strdup(var), res->value = NULL, res);
	if (equal - var > 0)
		append = (*(equal - 1) == '+');
	if (append)
		return (append_keyval(var, res, equal));
	res->key = ft_strndup(var, equal - var);
	res->value = NULL;
	if (*(equal + 1))
		res->value = ft_strdup(equal + 1);
	return (res);
}

static t_keyval	*append_keyval(char *var, t_keyval *res, const char *equal)
{
	res->key = ft_strndup(var, equal - var - 1);
	if (!res->key)
	{
		print_error(alloc_error, "(create_keyval..)");
		return (NULL);
	}
	res->value = get_env_var_value(res->key);
	if (!res->value)
		res->value = ft_strjoin_secure("", equal + 1);
	else
		res->value = ft_strjoin_secure(res->value, equal + 1);
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
