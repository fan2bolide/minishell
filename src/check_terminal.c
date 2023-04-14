/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_terminal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:35:09 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/14 14:35:10 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_terminal(void)
{
	const char	*terminals_that_accept_colours[7] = {"xterm-256color", \
	"gnome-256color", "konsole-256color", "rxvt-unicode-256color", \
	"konsole-16-color", "xterm", NULL};
	char		*actual_terminal;
	int			i;

	i = 0;
	actual_terminal = get_env_var_value("TERM");
	if (!actual_terminal)
		return (false);
	while (terminals_that_accept_colours[i])
	{
		if (ft_strequ(terminals_that_accept_colours[i], actual_terminal))
			return (true);
		i++;
	}
	return (false);
}
