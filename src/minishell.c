/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 02:59:28 by bajeanno          #+#    #+#             */
/*   Updated: 2023/02/20 21:14:30 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/head/libft.h"


void	welcome_msg(void)
{
	ft_printf("Welcome to minishell\n");
}

void	read_line(void)
{
	char	*res;

	res = readline(" > ");
	ft_printf(res);
}

void	msh_parser(char * line)
{

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
2) Display prompt
3) Readline
4) Parse line
5) execute commands



 */
