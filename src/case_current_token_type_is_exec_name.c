/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_current_token_type_is_exec_name.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 23:33:32 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd_line.h"

static void		\
get_exec_name_and_args(t_token_list *token_lst_cursor, t_cmd *cmd);
static void		\
cpy_splits_in_cmd_argv(t_cmd *cmd, char *const *splits, \
int *i, size_t *cmd_tab_size);

void	case_current_token_type_is_exec_name(t_token_list *token_lst_cursor, \
t_cmd *cmd)
{
	get_exec_name_and_args(token_lst_cursor, cmd);
	free(cmd->path);
	if (is_builtin(cmd->argv[0]) < 0)
		cmd->path = get_path(cmd->argv[0], g_envp_lst);
	else
	{
		cmd->path = ft_strdup("builtin");
		if (!cmd->path)
			print_error(error_occured, "");
	}
}

static void	get_exec_name_and_args(t_token_list *token_lst_cursor, t_cmd *cmd)
{
	t_token	*current_token;
	char	**splits;
	int		i;
	size_t	cmd_tab_size;

	cmd_tab_size = token_cmd_line_size(token_lst_cursor) + 1;
	cmd->argv = ft_calloc(cmd_tab_size, sizeof(char *));
	i = 0;
	if (cmd_tab_size > 1)
	{
		current_token = token_lst_cursor->content;
		splits = ft_old_split(current_token->content, ' ');
		cpy_splits_in_cmd_argv(cmd, splits, &i, &cmd_tab_size);
		token_lst_cursor = token_lst_cursor->next;
		free(splits);
	}
	while (cmd_tab_size > 1)
	{
		current_token = token_lst_cursor->content;
		cmd->argv[i++] = ft_strdup(current_token->content);
		token_lst_cursor = token_lst_cursor->next;
		cmd_tab_size--;
	}
	cmd->argv[i] = NULL;
}

static void	cpy_splits_in_cmd_argv(t_cmd *cmd, \
char *const *splits, int *i, size_t *cmd_tab_size)
{
	int		j;

	j = 0;
	while (splits[j])
	{
		cmd->argv[(*i)++] = splits[j++];
		(*cmd_tab_size)--;
	}
}
