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

t_keyval_list	*envp_lst;

int				get_exit_code(void);

/// sets the system calls for minishell signal handling
/// \param sig_handler
static int	setup_signals(void(sig_handler)(int))
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
		ft_printf(ANSI_RED "\r \001➜\002 " ANSI_RESET);
	}
	if (sig == SIGQUIT)
	{
		if (get_exit_code() == 0)
			ft_printf(ANSI_BLUE "\r     \r \001➜\002 " ANSI_RESET);
		else
			ft_printf(ANSI_RED "\r     \r \001➜\002 " ANSI_RESET);
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
		update_exit_code(130);
}

///updates the env '?' variable with the exit code of the last program called
void	update_exit_code(int exit_code)
{
	char	*new_exit_code;

	new_exit_code = ft_itoa(exit_code);
	free(envp_lst->content->value);
	envp_lst->content->value = new_exit_code;
}

/// sets the value of env's '?' variable to 0
/// \return 1 if allocation fails, 0 else
int	set_exit_code(void)
{
	t_keyval_list	*new;

	new = malloc(sizeof(t_keyval_list));
	if (!new)
		return (1);
	new->next = envp_lst;
	new->content = malloc(sizeof(t_keyval));
	if (!new->content)
		return (free(new), 1);
	new->content->key = ft_strdup("?");
	new->content->value = ft_strdup("0");
	envp_lst = new;
	return (0);
}

/// \return the value of env's '?' variable
int	get_exit_code(void)
{
	return (ft_atoi(envp_lst->content->value));
}

char	*prompt(void)
{
	char	*res;
	char	*tmp;

	if (!setup_signals(sig_handler_interactive_mode))
		return (NULL);
	if (get_exit_code())
		tmp = readline(ANSI_RED " \001➜\002 " ANSI_RESET);
	else
		tmp = readline(ANSI_BLUE " \001➜\002 " ANSI_RESET);
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

t_str_list	*convert_str_arr_into_new_str_list(char **array)
{
	t_str_list	*res;

	res = (t_str_list *)ft_lstnew(NULL);
	if (array == NULL)
		return (res);
	res->content = *array;
	array++;
	while (*array)
	{
		ft_lstadd_back((t_list **)&res, ft_lstnew(*array));
		array++;
	}
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
		ft_lstadd_back((t_list **)&res,
						ft_lstnew(create_keyval_from_env_var(*array)));
		array++;
	}
	return (res);
}

///assign correct values to global var 'envp_lst'
void	dup_envp(char **envp) //todo si env est NULL, créer ququchose quand même
{
	if (!envp)
	{
		envp_lst = NULL;
		return ;
	}
	envp_lst = convert_str_arr_into_new_keyval_list(envp);
	set_exit_code();
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
		prompt_res = prompt();
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
			return (0);
		cmd_lst = convert_token_lst_into_cmd_lst((t_token_list *)token_list);
		ft_lstclear((t_list **)&token_list, destroy_token);
		execute_cmd_line(cmd_lst);
		ft_lstclear((t_list **)&cmd_lst, (void (*)(void *)) & destroy_cmd);
	}
}
