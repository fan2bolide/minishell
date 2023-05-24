/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:30:45 by bajeanno          #+#    #+#             */
/*   Updated: 2023/05/24 16:30:46 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_colours_to_prompt(char *prompt)
{
	char	*res;

	if (!prompt)
		return (NULL);
	prompt = ft_strjoin_free_s1(prompt, ANSI_RESET);
	if (get_exit_code())
		prompt = ft_strjoin_free_s1(prompt, ANSI_RED" \001➜\002 "ANSI_RESET);
	else
	prompt = ft_strjoin_free_s1(prompt, ANSI_BLUE" \001➜\002 "ANSI_RESET);
	res = ft_strjoin(ANSI_BOLD_WHITE, prompt);
	free(prompt);
	return (res);
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*cwd;
	size_t	i;

	cwd = getcwd(NULL, 0);
	i = ft_strlen(cwd) - 1;
	while (i > 0 && cwd[i] != '/')
		i--;
	if (i)
		i++;
	prompt = ft_strdup(cwd + i);
	free(cwd);
	return (add_colours_to_prompt(prompt));
}

char	*clean_prompt_res(char *tmp)
{
	char	*res;

	res = ft_strtrim(tmp, " ");
	free(tmp);
	if (!ft_strequ(res, ""))
		add_history(res);
	return (res);
}

char	*prompt(int term_does_handle_color)
{
	char			*tmp;
	struct termios	term;
	char			*prompt;

	if (!setup_signals(sig_handler_interactive_mode) || \
		!backup_termios_and_disable_ctrl_backslash(&term))
		return (NULL);
	prompt = get_prompt();
	if (term_does_handle_color)
	{
		if (prompt)
			tmp = readline(prompt);
		else
			tmp = readline(ANSI_BLUE" \001➜\002 "ANSI_RESET);
	}
	else
		tmp = readline(" ➜ ");
	if (!restore_termios(&term) || \
		!setup_signals(sig_handler_execution_mode))
		return (NULL);
	if (tmp == NULL)
		return (ft_strdup("exit"));
	return (clean_prompt_res(tmp));
}
