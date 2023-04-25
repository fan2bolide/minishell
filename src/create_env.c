/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:25:17 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/25 19:25:21 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///creates a new keyval instance from the linux file "/etc/environment"
///and adds it to the envp list
void	add_path_to_envp(void)
{
	char			*path;
	int				fd;
	int				i;
	t_keyval_list	*new_keyval;

	fd = open("/etc/environment", O_RDONLY);
	if (fd < 0)
		return (print_error(no_file, "add_path_to_envp"));
	path = get_next_line(fd);
	i = 0;
	while (path[i] && path[i] != '=')
		i++;
	i++;
	ft_memmove(path, path + i, ft_strlen(path) - i + 1);
	path[ft_strlen(path) - 1] = '\0';
	new_keyval = malloc(sizeof(t_keyval_list));
	new_keyval->content = create_keyval();
	new_keyval->content->key = ft_strdup("PATH");
	new_keyval->content->value = ft_strtrim(path, "\" ");
	if (!new_keyval->content->value || !new_keyval->content->key)
		return (print_error(alloc_error, "add_path_to_envp"));
	ft_lstadd_back((t_list **)&g_envp_lst, (t_list *)new_keyval);
	free(path);
}

///assign correct values to global var 'envp_lst'
void	dup_envp(char **envp)
{
	char	*tmp;

	if (!*envp)
	{
		g_envp_lst = malloc(sizeof (struct s_keyval_list));
		g_envp_lst->next = NULL;
		g_envp_lst->content = create_keyval();
		g_envp_lst->content->key = ft_strdup("PWD");
		tmp = ft_calloc(1, 1024);
		getcwd(tmp, 1024);
		g_envp_lst->content->value = ft_strdup(tmp);
		free(tmp);
		add_path_to_envp();
	}
	else
		g_envp_lst = convert_str_arr_into_new_keyval_list(envp);
	if (!set_exit_code())
		return (ft_lstclear((t_list **)&g_envp_lst, destroy_keyval));
}
