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

char	*prompt(void)
{
	char	*res;
	char	*tmp;

	tmp = readline(" > ");
	if (tmp == NULL)
	{
		ft_printf("\r > exit\n");
		exit(1);
	}
	res = ft_strtrim(tmp, " ");
	free(tmp);
	add_history(res);
	return (res);
}

t_list *convert_arr_into_new_list(void **array)
{
	t_list *res;

	res = ft_lstnew(NULL);
	if (array == NULL)
		return (res);
	res->content = *array;
	array++;
	while(*array)
	{
		ft_lstadd_back(&res, ft_lstnew(*array));
		array++;
	}
	return (res);
}

t_list * dup_envp(char **envp)
{

	if (!envp)
		return (NULL);
	size_t sizeof_char_ptr = sizeof (char *);
//	res = ft_dup_arr((void **) envp, sizeof_char_ptr);
	return (convert_arr_into_new_list((void **)envp));

}

void sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt_res;
	t_list	*token_list;
	t_list	*curr;
	t_list 	*envp_lst;

	(void)argc;
	signal(SIGINT, sig_handler);
	pwd = getcwd(pwd, sizeof (pwd));
	ft_printf("pwd : %s\n", pwd);
	envp_lst = dup_envp(envp);
	welcome_msg();
	while (1)
	{
		prompt_res = prompt();
		token_list = get_main_token_list(prompt_res);
		free(prompt_res);
		curr = token_list;
		if (!curr)
			continue;
		token_list = token_parsing(token_list);
		if (!token_list)
			return (ft_printf("syntax error, aborting.\n"), 1);
		t_list *cmd_lst = convert_token_lst_into_cmd_lst(token_list, &envp_lst);
		execute_cmd_line(cmd_lst);
		ft_lstclear(&token_list, destroy_token);
	}
}
