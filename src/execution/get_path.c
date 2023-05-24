/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:47:34 by alevra            #+#    #+#             */
/*   Updated: 2023/04/12 01:54:33 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

static bool	key_exist(const t_keyval_list *envp_lst);
static int	search_path(t_keyval_list **envp_lst);
static bool	check_abs_or_rel_path(char **exec_name);
static char	*test_each_path(char *exec_name, char **paths);

char	*get_path(char *exec_name, t_keyval_list *envp_lst)
{
	char	**paths;

	if (!key_exist(envp_lst) || !exec_name || !*exec_name)
		return (NULL);
	if (check_abs_or_rel_path(&exec_name))
		return (exec_name);
	if (!search_path(&envp_lst))
		return (NULL);
	paths = ft_split(envp_lst->content->value, ':');
	if (!paths)
		return (print_error(alloc_error, "split"), NULL);
	return (test_each_path(exec_name, paths));
}

static char	*test_each_path(char *exec_name, char **paths)
{
	char	*path;
	int		i;

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin_w_slash(paths[i++], exec_name);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) != 0 || exec_name[0] == 0)
				printf("permission denied :%s\n", exec_name);
			return (ft_split_destroy(paths), path);
		}
		free(path);
	}
	return (ft_split_destroy(paths), NULL);
}

static bool	check_abs_or_rel_path(char **exec_name)
{
	if (!ft_strchr(*exec_name, '/'))
		return (false);
	if (access(*exec_name, F_OK) == 0)
	{
		if (access(*exec_name, X_OK) != 0)
			printf("permission denied :%s\n", *exec_name);
		*exec_name = ft_strdup(*exec_name);
		if (!*exec_name)
			print_error(alloc_error, "(get_path)");
		return (true);
	}
	return (false);
}

static int	search_path(t_keyval_list **envp_lst)
{
	const int	fail = 0;
	const int	success = 1;

	while (key_exist(*envp_lst) \
	&& ft_strequ((*envp_lst)->content->key, "PATH") == 0)
		*envp_lst = (*envp_lst)->next;
	if (!key_exist(*envp_lst) \
	|| ft_strequ((*envp_lst)->content->key, "PATH") == 0)
		return (fail);
	return (success);
}

static bool	key_exist(const t_keyval_list *envp_lst)
{
	return (envp_lst && envp_lst->content && envp_lst->content->key);
}
