/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:19:25 by alevra            #+#    #+#             */
/*   Updated: 2023/02/23 14:41:20 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_args(int argc, char **argv);

int	pipex(int argc, char **argv, char **envp)
{
	int			files[2];
	t_to_exec	*cmds;
	int			here_doc_option;

	here_doc_option = ft_strequ(argv[1], "here_doc");
	if (check_args(argc, argv) < 0)
		return (-1);
	if (!here_doc_option)
	{
		files[FILE_1] = open(argv[1], O_RDONLY);
		if (files[FILE_1] < 0)
			perror(argv[1]);
	}

	if (!here_doc_option)
		files[FILE_2] = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		files[FILE_2] = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);

	if (files[FILE_2] < 0)
		perror(argv[argc - 1]);

	cmds = (parser(argv, envp));
	if (!cmds)
	{
		if (!ft_strequ(argv[1], "here_doc"))
			close(files[FILE_1]);
		return (close(files[FILE_2]), -1);
	}
	if (execute_all_cmds(cmds, files) < 0)
		return (-1);
	return (close(files[FILE_2]), 0);
}

static int	check_args(int argc, char **argv)
{
	if (argc != 5)
		return (ft_printf("Incorrect number of args\n"), -1);
	if (argc < 5 || (ft_strequ(argv[1], "here_doc") && argc < 6))
		return (ft_printf("Not enough args\n"), -1);
	return (0);
}
