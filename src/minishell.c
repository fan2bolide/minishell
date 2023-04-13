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

///updates the env '?' variable with the exit code of the last program called
void	update_exit_code(int exit_code)
{
	char	*new_exit_code;

	new_exit_code = ft_itoa(exit_code);
	free(g_envp_lst->content->value);
	g_envp_lst->content->value = new_exit_code;
}

/// sets the value of env's '?' variable to 0
/// \return 1 if allocation fails, 0 else
bool	set_exit_code(void)
{
	t_keyval_list	*new;

	new = malloc(sizeof(t_keyval_list));
	if (!new)
		return (false);
	new->next = g_envp_lst;
	new->content = malloc(sizeof(t_keyval));
	if (!new->content)
		return (free(new), false);
	new->content->key = ft_strdup("?");
	new->content->value = ft_strdup("0");
	if (!new->content->key || !new->content->value)
	{
		free(new->content->key);
		free(new->content->value);
		free(new);
		return (false);
	}
	g_envp_lst = new;
	return (true);
}

/// \return the value of env's '?' variable
int	get_exit_code(void)
{
	return (ft_atoi(g_envp_lst->content->value));
}

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
	char	*tmp;

	if (!*envp)
	{
		g_envp_lst = malloc(sizeof (struct s_keyval_list));
		g_envp_lst->next = NULL;
		g_envp_lst->content = create_keyval();
		g_envp_lst->content->key = ft_strdup("PWD");
		tmp = ft_calloc(1, 1024);
		getcwd(tmp, 1024);
		g_envp_lst->content->value = ft_strdup(tmp);
		free(tmp);
	}
	else
		g_envp_lst = convert_str_arr_into_new_keyval_list(envp);
	if (!set_exit_code())
		return (ft_lstclear((t_list **)&g_envp_lst, destroy_keyval));
}

int	main(int argc, char **argv, char **envp)
{
	char			*prompt_res;
	t_token_list	*token_list;
	t_cmd_list		*cmd_lst;
	bool			term_color;

	(void)argc;
	(void)argv;
	term_color = true;
	if (!*envp)
		term_color = false;
	dup_envp(envp);
	while (1)
	{
		prompt_res = prompt(term_color);
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
	}
}
