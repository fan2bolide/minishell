/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:47:34 by alevra            #+#    #+#             */
/*   Updated: 2023/02/23 15:25:33 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

static void	freepath(char **paths);
static char	*ft_strjoin_w_slash(char *incomplete_path, char *cmd);

char	*get_path(char *exec_name, t_keyval_list *envp_lst)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	if (!envp_lst || !exec_name)
		return (NULL);
	while (ft_strequ(envp_lst->content->key, "PATH") == 0)
		envp_lst = envp_lst->next;
	paths = ft_split(envp_lst->content->value, ':');
	if (!paths)
		return (ft_putstr_fd("An error occurred (split)\n", 2), NULL);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin_w_slash(paths[i++], exec_name);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) != 0 || exec_name[0] == 0)
				ft_printf("permission denied :%s\n", exec_name);
			return (free(paths), path);
		}
		free(path);
	}
	return (free(paths), NULL);
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
			ft_putstr_fd("An error occurred (ft_strjoin_w_slash)\n", 2);
		free(path_w_slash);
		return (path);
	}
	else
		return (ft_strdup(cmd));
}

static void	freepath(char **paths)
{
	int	i;

	i = 0;
	while (paths && paths[i])
		free(paths[i++]);
}
