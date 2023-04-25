/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 02:59:28 by bajeanno          #+#    #+#             */
/*   Updated: 2023/03/01 20:32:28 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_keyval_list	*g_envp_lst;

char	*prompt(int term_does_handle_color)
{
	char	*res;
	char	*tmp;

	if (!setup_signals(sig_handler_interactive_mode))
		return (NULL);
	if (term_does_handle_color)
	{
		if (get_exit_code())
			tmp = readline(ANSI_RED " \001➜\002 " ANSI_RESET);
		else
			tmp = readline(ANSI_BLUE " \001➜\002 " ANSI_RESET);
	}
	else
		tmp = readline(" ➜ ");
	if (tmp == NULL)
		return (ft_strdup("exit"));
	res = ft_strtrim(tmp, " ");
	free(tmp);
	if (!ft_strequ(res, ""))
		add_history(res);
	if (!setup_signals(sig_handler_execution_mode))
		return (NULL);
	return (res);
}

///converts char *envp to key/value list so we can use and update it
t_keyval_list	*convert_str_arr_into_new_keyval_list(char **array)
{
	t_keyval_list	*res;

	res = (t_keyval_list *)ft_lstnew(NULL);
	if (array == NULL)
		return (res);
	res->content = create_keyval_from_env_var(*array);
	array++;
	while (*array)
	{
		ft_lstadd_back((t_list **)&res, \
		ft_lstnew(create_keyval_from_env_var(*array)));
		array++;
	}
	return (res);
}

int	main(int argc, char **argv, char **envp)
{
	char			*prompt_res;
	t_token_list	*token_list;
	t_cmd_list		*cmd_lst;

	(void)argc;
	(void)argv;
	dup_envp(envp);
	while (1)
	{
		prompt_res = prompt(*envp && check_terminal());
		if (!prompt_res)
			return (perror("signal setup failed: "), 1);
		token_list = get_main_token_list(prompt_res);
		free(prompt_res);
		if (!token_list)
			continue ;
		token_list = token_parsing(token_list);
		if (!token_list)
			continue ;
		if (!expand_tokens_from_list(token_list))
			continue ;
		cmd_lst = convert_token_lst_into_cmd_lst((t_token_list *)token_list);
		ft_lstclear((t_list **)&token_list, destroy_token);
		execute_cmd_line(cmd_lst);
	}
}
