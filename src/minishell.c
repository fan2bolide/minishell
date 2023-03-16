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
		perror("readline failed\n");
		exit(0);
	}
	res = ft_strtrim(tmp, " ");
	free(tmp);
	add_history(res);
	return (res);
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt_res;
	t_list	*token_list;
	t_list	*curr;

	(void)argc;
	welcome_msg();
	expand_content(NULL);
	prompt_res = prompt();
	int i = 0;
	while (!ft_strequ(prompt_res, "exit"))
	{
		token_list = get_main_token_list(prompt_res);
		free(prompt_res);
		curr = token_list;
		if (!curr)
		{
			prompt_res = prompt();
			continue;
		}
		while (curr)
		{
			if (((t_token *)curr->content)->type == error)
			{
				ft_printf("an error occurred.\n");
				break;
			}
			print_token(curr->content);
			curr = curr->next;
			i++;
		}
		token_list = token_parsing(token_list);
		if (!token_list)
			return (ft_printf("syntax error, aborting.\n"), 1);
		t_list *cmd_lst = convert_token_lst_into_cmd_lst(token_list, envp);
		execute_cmd_line(cmd_lst);
		ft_lstclear(&token_list, destroy_token);
		prompt_res = prompt();
	}
	free(prompt_res);
	return (0);
}
