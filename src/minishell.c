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
#include "execute_cmd_line.h"

void	welcome_msg(void)
{
	//ft_printf(" ███████████                      █████             \n");
	//ft_printf("░█░░░███░░░█                     ░░███              \n");
	//ft_printf("░   ░███  ░  █████ ████ ████████  ░███████   ██████ \n");
	//ft_printf("    ░███    ░░███ ░███ ░░███░░███ ░███░░███ ███░░███\n");
	//ft_printf("    ░███     ░███ ░███  ░███ ░░░  ░███ ░███░███ ░███\n");
	//ft_printf("    ░███     ░███ ░███  ░███      ░███ ░███░███ ░███\n");
	//ft_printf("    █████    ░░████████ █████     ████████ ░░██████ \n");
	//ft_printf("   ░░░░░      ░░░░░░░░ ░░░░░     ░░░░░░░░   ░░░░░░  \n");
	ft_printf("________             ______              ______      ___________\n");
	ft_printf("___  __/___  ___________  /_________________  /_________  /__  /\n");
	ft_printf("__  /  _  / / /_  ___/_  __ \\  __ \\_  ___/_  __ \\  _ \\_  /__  / \n");
	ft_printf("_  /   / /_/ /_  /   _  /_/ / /_/ /(__  )_  / / /  __/  / _  /  \n");
	ft_printf("/_/    \\__,_/ /_/    /_.___/\\____//____/ /_/ /_/\\___//_/  /_/   \n");
}

void	update_exit_code(int exit_code)
{
	char *new_exit_code;

	new_exit_code = ft_itoa(exit_code);
	free(envp_lst->content->value);
	envp_lst->content->value = new_exit_code;
}

int	set_exit_code(void)
{
	t_keyval_list *new;

	new = malloc(sizeof (t_keyval_list));
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

int	get_exit_code(void)
{
	return (ft_atoi(envp_lst->content->value));
}

char	*prompt(void)
{
	char	*res;
	char	*tmp;

	if (get_exit_code())
		tmp = readline(ANSI_RED" ➜ "ANSI_RESET);
	else
		tmp = readline(ANSI_BLUE" ➜ "ANSI_RESET);
	if (tmp == NULL)
	{
		ft_printf("\r ➜ exit\n");
		exit(1);
	}
	res = ft_strtrim(tmp, " ");
	free(tmp);
	add_history(res);
	return (res);
}

t_str_list * convert_str_arr_into_new_str_list(char **array)
{
	t_str_list *res;

	res = (t_str_list *)ft_lstnew(NULL);
	if (array == NULL)
		return (res);
	res->content = *array;
	array ++;
	while(*array)
	{
		ft_lstadd_back((t_list **)&res, ft_lstnew(*array));
		array ++;
	}
	return (res);
}

t_keyval_list * convert_str_arr_into_new_keyval_list(char **array)
{
	t_keyval_list *res;

	res = (t_keyval_list *)ft_lstnew(create_keyval());
	if (array == NULL)
		return (res);
	res->content = create_keyval_from_env_var(*array);

	array ++;
	while(*array)
	{
		ft_lstadd_back((t_list **)&res, ft_lstnew(create_keyval_from_env_var(*array)));
		array ++;
	}
	return (res);
}


//assign correct values to glabal var 'envp_lst'
void dup_envp(char **envp)
{
	if (!envp)
	{
		envp_lst = NULL;
		return ;
	}
	envp_lst = convert_str_arr_into_new_keyval_list(envp);
	set_exit_code();
}

void sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		update_exit_code(130);
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		ft_printf(ANSI_RED"\r ➜ "ANSI_RESET);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt_res;
	t_list	*token_list;
	t_list	*curr;


	(void)argc;
	signal(SIGINT, sig_handler);
	dup_envp(envp);
	welcome_msg();
	while (1)
	{
		prompt_res = prompt();
		if (ft_strequ(prompt_res, "exit"))
			return (0);
		if (ft_strequ(prompt_res, "$?"))
		{
			ft_printf("%d\n", get_exit_code());
			continue;
		}
		token_list = get_main_token_list(prompt_res);
		free(prompt_res);
		curr = token_list;
		if (!curr)
			continue;
		token_list = token_parsing(token_list);
		if (!token_list)
			return (ft_printf("syntax error, aborting.\n"), 1);
		if (!expand_tokens_from_list(token_list))
			return (0);
		t_cmdlist *cmd_lst = convert_token_lst_into_cmd_lst(token_list);
		execute_cmd_line(cmd_lst);
		ft_lstclear(&token_list, destroy_token);
	}
}
