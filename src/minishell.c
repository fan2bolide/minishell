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

//debug
void	debug_aurel(int argc, char **argv, char **envp)
{
	t_list	*token_list;

	if (argc > 1 && ft_strequ(argv[1], "debug") == 1)
	{
		token_list = get_sample_tokens();
//		convert_token_lst_into_cmd_lst(token_list); need envp here
	}
}

void	welcome_msg(void)
{
	ft_printf(" ███████████                      █████                      █████               ████  ████ \n");
	ft_printf("░█░░░███░░░█                     ░░███                      ░░███               ░░███ ░░███ \n");
	ft_printf("░   ░███  ░  █████ ████ ████████  ░███████   ██████   █████  ░███████    ██████  ░███  ░███ \n");
	ft_printf("    ░███    ░░███ ░███ ░░███░░███ ░███░░███ ███░░███ ███░░   ░███░░███  ███░░███ ░███  ░███ \n");
	ft_printf("    ░███     ░███ ░███  ░███ ░░░  ░███ ░███░███ ░███░░█████  ░███ ░███ ░███████  ░███  ░███ \n");
	ft_printf("    ░███     ░███ ░███  ░███      ░███ ░███░███ ░███ ░░░░███ ░███ ░███ ░███░░░   ░███  ░███ \n");
	ft_printf("    █████    ░░████████ █████     ████████ ░░██████  ██████  ████ █████░░██████  █████ █████\n");
	ft_printf("   ░░░░░      ░░░░░░░░ ░░░░░     ░░░░░░░░   ░░░░░░  ░░░░░░  ░░░░ ░░░░░  ░░░░░░  ░░░░░ ░░░░░ \n");
}

char	*prompt(void)
{
	char	*res;
	char	*tmp;

	tmp = readline(" > ");
	res = ft_strtrim(tmp, " \n");
	free(tmp);
	return (res);
}

int	main(int argc, char **argv, char **envp)
{


	char	*prompt_res;
		t_list *token_list;
		t_list *curr;

	(void)argc;
	(void)argv;
//	debug_aurel(argc, argv, envp);
	welcome_msg();
	prompt_res = prompt();
	int i = 0;
	while (!ft_strequ(prompt_res, "exit"))
	{
		token_list = get_token_list(prompt_res);
		curr = token_list;
		while (curr)
		{
			if (((t_token *)curr->content)->type == error)
			{
				ft_printf("an error occurred.\n");
				break;
			}
			else{
				t_list *cmd_lst = convert_token_lst_into_cmd_lst(token_list, envp);
				execute_cmd_line(cmd_lst);
			}
//			print_token(curr->content);
			curr = curr->next;
			i++;
		}
		token_list = token_parsing(token_list);
		if (!token_list)
			return (ft_printf("syntax error, aborting.\n"), 1);
		ft_lstclear(&token_list, destroy_token);
		free(prompt_res);
		prompt_res = prompt();
	}
	free(prompt_res);
	return (0);
}

/*

The minishell sould :

1) Display "Welcome to minishell msg"
loop :
2) ??
3) Readline + diplay prompt (ls )
4) Parse line

		infile cmd1 cmd2 outfile append
-->		< infile  cmd1 | cmd2 >> outfile

		infile cmd1 cmd2 outfile trunc
-->		infile << cmd1 | cmd2 > outfile


 > infile ldsjflsdkjflksdjflkjdsf
--> execute_cmd_line( < pldsjflsdkjflksdjflkjdsf | dff >> sfdsdf| ksjdbfkjsd);


 > oihteoirhtoerhto;
--> execute_cmd_line(oihteoirhtoerhto, 0, 0);


split les phrases (une phrase = un appel de execute_cmd_line)
efface les barres |
... | ... | .. > FILE | sdkjdsjf | sdf








ls "chemin" | cat -e >> outfile1 | wc -l



-ls "args"
- cat -e
- wc -l
- fichier

Il faudra appeler n fois execute_cmd_line
n represente le nombre de ofis ou on peut fractionner la ligne
On peut fractionner quand on est sur qu'un pipe ne prend aucune entree

5) execute commands

routine -> execute_cmd_line

 */
