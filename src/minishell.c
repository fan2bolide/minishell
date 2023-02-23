/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 02:59:28 by bajeanno          #+#    #+#             */
/*   Updated: 2023/02/21 01:34:31 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/head/libft.h"

void	welcome_msg(void)
{
	ft_printf("Welcome to marrakesh\n");
}

void	read_line(void)
{
	char	*res;

	res = readline(" > ");
	ft_printf(res);
}

char	**msh_parser(char *line)
{
	return (ft_split(line, ' '));
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	welcome_msg();
	msh_parser(read_line());
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
--> pipex( < pldsjflsdkjflksdjflkjdsf | dff >> sfdsdf| ksjdbfkjsd);


 > oihteoirhtoerhto;
--> pipex(oihteoirhtoerhto, 0, 0);


split les phrases (une phrase = un appel de pipex)
efface les barres |
... | ... | .. > FILE | sdkjdsjf | sdf








ls "chemin" | cat -e >> outfile1 | autrechose



-ls "args"
- cat -e
- wc -l
- fichier

Il faudra appeler n fois pipex
n represente le nombre de ofis ou on peut fractionner la ligne
On peut fractionner quand on est sur qu'un pipe ne prend aucune entree

5) execute commands

routine -> pipex

 */
