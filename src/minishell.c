/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 02:59:28 by bajeanno          #+#    #+#             */
/*   Updated: 2023/02/23 15:52:44 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"
#include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

void	welcome_msg(void)
{
	ft_printf("Welcome to marrakesh\n");
}

char	*prompt(void)
{
	char	*res;

	res = readline(" > ");
	return (res);
}

char	**msh_parser(char *line)
{
	char	**splits;

	splits = ft_split(line, ' ');
	return (splits);
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt_res;

	(void)argc;
	(void)argv;
	welcome_msg();
	prompt_res = prompt();
	execute_cmd_line(prompt_res, envp);
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
