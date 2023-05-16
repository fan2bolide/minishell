/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_handling.c                                :+:      :+:    :+:   */
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

int backup_termios(struct termios *termios_to_backup)
{
	if (!isatty(STDERR_FILENO))
		return (1);
	if (tcgetattr(STDERR_FILENO, termios_to_backup) < 0)
		return (print_error(error_occured, "unable to backup terminal"), 0);
	return (1);
}

int disable_ctrl_backslash(void)
{
	struct termios	termios;

	if (!isatty(STDERR_FILENO))
		return (1);
	if (tcgetattr(STDERR_FILENO, &termios) < 0)
		return (print_error(error_occured, "unable to disable SIGQUIT"), 0);
	termios.c_cc[VQUIT] = 0;
	if (tcsetattr(STDERR_FILENO, TCSANOW, &termios) < 0)
		return (print_error(error_occured, "unable to disable SIGQUIT"), 0);
	return (1);
}

int restore_termios(struct termios *termios_to_restore)
{
	if (!isatty(STDERR_FILENO))
		return (1);
	if (tcsetattr(STDERR_FILENO, TCSANOW, termios_to_restore) < 0)
		return (print_error(error_occured, "unable to restore terminal"), 0);
	return (1);
}
