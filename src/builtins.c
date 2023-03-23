
#include "builtins.h"

void	exec_builtin(t_cmd *cmd, int to_read, int to_write)
{
	int type;
	type = is_builtin(cmd->argv[0]);
	if (type == 0)
		echo(cmd->argv, to_write);
	else if (type == 1)
		cd(cmd);
	else if (type == 2)
		ft_putstr_fd("pwd\n", to_write);
	else if (type == 3)
		export(cmd->argv, cmd->envp_lst_ptr);
	else if (type == 4)
		unset(cmd->argv[1], cmd->envp_lst_ptr);
	else if (type == 5)
		env(*(cmd->envp_lst_ptr), to_write);

}
// returns -1 if str is not a builtins
// returns [0...6] if str is builtins
int	is_builtin(char *str)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (i < 7)
		if (ft_strequ(str, builtins[i++]))
			return (i - 1);
	return (-1);
}

void	echo(char **argv, int to_write) // adapt
{
	char *msg;
	int 	option_n;

	if (!argv[1])
		return;
	msg = argv[1]; // need to be improved
	option_n = 0;
	if (argv[1] && argv[2])
		option_n = ft_strequ(argv[2], "-n"); //need to be improved
	ft_putstr_fd(msg, to_write);
	if (!option_n)
		ft_putstr_fd("\n", to_write);
}

/**
 * DO NOT FREE THE RETURN VALUE
 * @param var_name
 * @param envp
 * @return value of the variable <varname> in environment
 */
char *get_env_var_value(char *var_name, t_str_list **envp)
{
	int		i;
	t_str_list	*curr;

	i = 0;
	curr = *envp;
	if (!var_name || !*envp)
		return NULL;
	while (curr && !str_starts_with(curr->content, var_name))
		curr = curr->next;
	if (!curr)
		return (NULL);
	while (curr->content[i] && curr->content[i] != '=')
		i++;
	if (curr->content[i])
		i++;
	return (curr->content + i);
}

void	export(char **argv, t_str_list **envp_lst_ptr)
{
	t_str_list *envp_lst_ptr_cpy = *envp_lst_ptr;
	while(envp_lst_ptr_cpy->next && ft_strcmp(argv[1], envp_lst_ptr_cpy->next->content) > 0)
	{
		(envp_lst_ptr_cpy) = (envp_lst_ptr_cpy)->next;
	}
	t_str_list *tmp = envp_lst_ptr_cpy->next;
	envp_lst_ptr_cpy->next = (t_str_list *)ft_lstnew(argv[1]);
	envp_lst_ptr_cpy->next->next = tmp;
}

/**
 *
 * @param str
 * @param keyword
 * @return 1 if str starts with keyword, 0 if not
 */
int str_starts_with(char *str, char *keyword)
{
	int res = ft_strncmp(str, keyword, ft_strlen(keyword));
	if (res == 0)
		return (1);
	return (0);
}

void	unset(char *var_to_unset, t_str_list **envp_lst_ptr)
{
	char **new_envp;
	size_t envp_size;
	t_str_list *envp_lst;

	envp_lst = *envp_lst_ptr;
//	if (!get_env_var_value(var_to_unset, envp_lst_ptr))
//		return;
	if (!var_to_unset)
		return((void)0);
//	envp_size = ft_arrsize((void **) envp_lst_ptr);
//	new_envp = ft_calloc(envp_size, 1);
//	if (!new_envp)
//		return (ft_printf("%s : An error occurred.\n", __FUNCTION__ ), (void)0);
	if (str_starts_with(envp_lst->content, ft_strjoin(var_to_unset, "=")))
	{
		//free(envp_lst->content);
		envp_lst_ptr = &(envp_lst->next);
	}
	else
	{
		while (envp_lst && \
				envp_lst->next && \
				!str_starts_with(envp_lst->next->content, ft_strjoin(var_to_unset, "=")))
			envp_lst = envp_lst->next;


		if(envp_lst->next)
		{
			t_str_list *elemnt_to_del = envp_lst->next;
//			free(elemnt_to_del->content);
			envp_lst->next = elemnt_to_del->next;
//			free(elemnt_to_del);
		}
	}
}

void env(t_str_list *envp_lst, int to_write)
{
	int i = 0;

	while (envp_lst)
	{
		ft_putstr_fd(ft_strjoin((char *)envp_lst->content, "\n"), to_write);
		envp_lst = envp_lst->next;
	}
}

void	trim_last_folder_if_possible(char *pwd)
{
	char	*last_slash;
	char 	*new_pwd;
	int 	i;

	i = 0;
	if (ft_strequ(pwd, "/"))
		return ;
	last_slash=ft_strrchr(pwd, '/');
	new_pwd = malloc(sizeof (char) * (last_slash - pwd) + 1);
	if (!new_pwd)
		return (ft_printf("turboshell: cd: an error occurred\n"), (void) 0);
	while (i < (last_slash - pwd))
	{
		new_pwd[i] = pwd[i];
		i ++;
	}
	new_pwd[i] = 0;
	free(pwd);
	pwd = new_pwd;
}

void update_pwd(char *dir, t_str_list *envp_lst)
{
	int i = 0;
	char *new_pwd;

	if (!envp_lst)
		return ;
	if (ft_strequ(dir, ".."))
		return (trim_last_folder_if_possible(pwd));
	new_pwd = ft_strjoin(pwd, "/");
	new_pwd = ft_strjoin(new_pwd, dir);
	free(pwd);
	pwd = new_pwd;
//	while (!str_starts_with(envp_lst_ptr[i], "PWD="))
//		i++;
//	if (!envp_lst_ptr[i])
//		return ;
//	free(envp_lst_ptr[i]);
//	envp_lst_ptr[i] = ft_strjoin("PWD=", pwd);
}

void cd(t_cmd *cmd)
{
	struct stat st;
	char 		*dir;

	dir = cmd->argv[1]; //need to be improved
	if (stat(dir, &st) < 0)
		return(perror("turboshell: cd:"), (void)0);
	if ((st.st_mode & S_IFMT) != S_IFDIR)
		return(ft_printf("turboshell: cd: %s: Not a directory\n", dir), (void)0);
	if (st.st_mode & S_IRUSR)
		update_pwd(dir, (cmd->envp_lst_ptr));
	else
		ft_printf("turboshell: cd: %s: Permission denied\n", dir);
}