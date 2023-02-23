/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:47:34 by alevra            #+#    #+#             */
/*   Updated: 2023/02/16 16:24:44 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	freepath(char **paths);
static char	*ft_strjoin_w_slash(char *incomplete_path, char *cmd);

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	if (!envp || !envp[0])
		return (NULL);
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (ft_printf("An error occured (split)\n"), NULL);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin_w_slash(paths[i++], cmd);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) != 0 || cmd[0] == 0)
				ft_printf("permission denied :%s\n", cmd);
			return (freepath(paths), free(paths), path);
		}
		free(path);
	}
	return (freepath(paths), free(paths), NULL);
}

static char	*ft_strjoin_w_slash(char *incomplete_path, char *cmd)
{
	char	*path_w_slash;
	char	*path;

	if (!ft_strnstr(cmd, "/", ft_strlen(cmd)))
	{
		path_w_slash = ft_strjoin(incomplete_path, "/");
		path = ft_strjoin(path_w_slash, cmd);
		if (!path || !path_w_slash)
			ft_printf("An error occured while finding the cmd path\n");
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
