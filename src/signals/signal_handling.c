/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 05:49:46 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/12 05:49:47 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// sets the system calls for minishell signal handling
/// \param sig_handler
int	setup_signals(void (*sig_handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = sig_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (0);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (0);
	return (1);
}

/**
 * gets called when receiving a sigint or sigquit
 * if sigint then readline ona newline and set exitcode to 130 according to bash
 * if sigquit then just rewrite the prompt and continue reading
 * @param sig
 */
void	sig_handler_interactive_mode(int sig)
{
	if (sig == SIGINT)
	{
		update_exit_code(130);
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		if (!check_terminal())
			return (printf("\r ➜ "), (void)0);
		printf(ANSI_RED "\r \001➜\002 " ANSI_RESET);
	}
}

/**
 * gets called when receiving a sigint or sigquit while in execution mode
 * if sigint then update exit code to 130 according to bash
 * if sigquit then do nothing
 * @param sig
 */
void	sig_handler_execution_mode(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		update_exit_code(130);
	}
}

/**
 * gets called when receiving a sigint or sigquit while in heredoc mode
 * if sigint then exit as a failure so the main process knows how to handle it
 * @param sig
 */
void	sig_handler_heredoc_mode(int sig)
{
	if (sig == SIGINT)
		exit(EXIT_FAILURE);
}
