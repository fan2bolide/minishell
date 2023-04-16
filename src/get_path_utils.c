/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:25:43 by alevra            #+#    #+#             */
/*   Updated: 2023/02/08 22:12:59 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

char	*ft_strjoin_w_slash(char *incomplete_path, char *cmd)
{
	char	*path_w_slash;
	char	*path;

	if (!ft_strnstr(cmd, "/", ft_strlen(cmd)))
	{
		path_w_slash = ft_strjoin_secure(incomplete_path, "/");
		path = ft_strjoin_secure(path_w_slash, cmd);
		if (!path || !path_w_slash)
			print_error(alloc_error, "strjoin_w_slash");
		free(path_w_slash);
		return (path);
	}
	else
		return (ft_strdup(cmd));
}
