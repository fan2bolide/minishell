/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:52:16 by alevra            #+#    #+#             */
/*   Updated: 2023/02/16 19:42:49 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	how_many_args(char **str);
static int	try_to_set_elmt_zero_case_heredoc(t_to_exec *to_exec_tab,
				char **argv);
static int	check_here_doc(char *str);

/*
BEHAVIOR EXAMPLE:

./pipex infile "cmd1" | "cmd2 -flagcmd2" | aldhsk | dsjfkjsd outfile (classic case aka hd = 0)
	- to_exec_tab size : how_many_args(&argv[2 + 0]) + 1 + 0
	- to_exec_tab[0].cmd[0] = cmd1
	-                ...[1] = NULL
	- to_exec_tab[1].cmd[0] = cmd2
	-                   [1] = -flagcmd2
	-                   [2] = NULL
	- to_exec_tab[2].cmd[0] = NULL

./pipex infile "cmd1" | cmd2  > flagcmd2 | aldhsk | dsjfkjsd outfile (classic case aka hd = 0)
	- to_exec_tab size : how_many_args(&argv[2 + 0]) + 1 + 0
	- to_exec_tab[0].cmd[0] = cmd1
	-                ...[1] = NULL
	- to_exec_tab[1].cmd[0] = cmd2
	-                   [1] = -flagcmd2
	-                   [2] = NULL
	- to_exec_tab[2].cmd[0] = NULL

./pipex here_doc DELIMITER "cmd1" "cmd2" outfile (here_doc case aka hd = 1)
	- to_exec_tab size :  how_many_args(&argv[2 + 1]) + 1 + 1
	- to_exec_tab[0].cmd[0] = here_doc
	-                ...[1] = DELIMITER
	- to_exec_tab[1].cmd[0] = cmd1
	- to_exec_tab[2].cmd[0] = cmd2
	- to_exec_tab[3].cmd[0] = NULL
 */
t_to_exec	*parser(char **argv, char **envp)
{
	t_to_exec	*to_exec_tab;
	int			i;
	int			hd;

	i = 0;
	hd = check_here_doc(argv[1]);
	to_exec_tab = ft_calloc(how_many_args(&argv[2 + hd]) + 1 + hd,
			sizeof(t_to_exec));
	if (!to_exec_tab)
		return (NULL);
	if (hd && try_to_set_elmt_zero_case_heredoc(to_exec_tab, argv) < 0)
		return (ft_printf("Allocation memory error\n"), NULL);
	i = 0 + hd;
	while (argv[i + 2 + 1])
	{
		to_exec_tab[i].cmd = ft_split(argv[i + 2], ' ');
		if (!to_exec_tab[i].cmd)
			return (ft_printf("An error occured (parsing)\n"), NULL);
		to_exec_tab[i].path = get_path(to_exec_tab[i].cmd[0], envp);
		to_exec_tab[i].envp = envp;
		i++;
	}
	to_exec_tab[i].cmd = NULL;
	return (to_exec_tab);
}

static int	check_here_doc(char *str)
{
	if (BONUS)
		if (ft_strequ(str, "here_doc"))
			return (1);
	return (0);
}

static int	try_to_set_elmt_zero_case_heredoc(t_to_exec *to_exec_tab,
												char **argv)
{
	to_exec_tab[0].cmd = ft_calloc(3, sizeof(char *));
	if (!to_exec_tab[0].cmd)
		return (free(to_exec_tab), -1);
	to_exec_tab[0].cmd[0] = ft_strdup("here_doc");
	to_exec_tab[0].cmd[1] = ft_strdup(argv[2]);
	to_exec_tab[0].path = ft_strdup("here_doc");
	if (!to_exec_tab[0].cmd[0] || !to_exec_tab[0].cmd[1]
		|| !to_exec_tab[0].path)
	{
		free(to_exec_tab[0].cmd[0]);
		free(to_exec_tab[0].cmd[1]);
		free(to_exec_tab[0].path);
		free(to_exec_tab[0].cmd);
		return (free(to_exec_tab), -1);
	}
	to_exec_tab[0].envp = NULL;
	return (0);
}

static int	how_many_args(char **str)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i][0] != '-')
			res++;
		i++;
	}
	return (res);
}
