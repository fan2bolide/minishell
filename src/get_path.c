/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienlevra <aurelienlevra@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:47:34 by alevra            #+#    #+#             */
/*   Updated: 2023/04/12 01:54:33 by aurelienlev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

//static void	freepath(char **paths);
static char	*ft_strjoin_w_slash(char *incomplete_path, char *cmd);

char	*get_path(char *exec_name, t_keyval_list *envp_lst)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	if (!envp_lst || !envp_lst->content || !envp_lst->content->key || !exec_name || !*exec_name)
		return (NULL);
	while (envp_lst && envp_lst->content && envp_lst->content->key && ft_strequ(envp_lst->content->key, "PATH") == 0)
		envp_lst = envp_lst->next;
	if (!envp_lst ||  !envp_lst->content || !envp_lst->content->key || ft_strequ(envp_lst->content->key, "PATH") == 0)
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
