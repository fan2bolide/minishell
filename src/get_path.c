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

static char	*ft_strjoin_w_slash(char *incomplete_path, char *cmd);
static bool	key_exist(const t_keyval_list *envp_lst);
int			search_path(t_keyval_list **envp_lst);

bool check_abs_or_rel_path(char **exec_name);

char	*get_path(char *exec_name, t_keyval_list *envp_lst)
{
	char	**paths;
	char	*path;
	int		i;

	if (!key_exist(envp_lst) || !exec_name || !*exec_name)
		return (NULL);
	if (check_abs_or_rel_path(&exec_name))
		return (exec_name);
	if (!search_path(&envp_lst))
		return (NULL);
	paths = ft_split(envp_lst->content->value, ':');
	if (!paths)
		return (print_error(error_occured, "split"), NULL);
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

bool check_abs_or_rel_path(char **exec_name)
{

	if (access(*exec_name, F_OK) == 0)
	{
		if (access(*exec_name, X_OK) != 0)
			printf("permission denied :%s\n", *exec_name); // a tester
		*exec_name = ft_strdup(*exec_name);
		if (!*exec_name)
			print_error(error_occured, "(get_path)");
		return (true);
	}
	return (false);
}


int	search_path(t_keyval_list **envp_lst)
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

static char	*ft_strjoin_w_slash(char *incomplete_path, char *cmd)
{
	char	*path_w_slash;
	char	*path;

	if (!ft_strnstr(cmd, "/", ft_strlen(cmd)))
	{
		path_w_slash = ft_strjoin_secure(incomplete_path, "/");
		path = ft_strjoin_secure(path_w_slash, cmd);
		if (!path || !path_w_slash)
			print_error(error_occured, "strjoin_w_slash");
		free(path_w_slash);
		return (path);
	}
	else
		return (ft_strdup(cmd));
}
