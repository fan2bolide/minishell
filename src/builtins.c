
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
		pwd(to_write);
	else if (type == 3)
		export(cmd->argv, to_write);
	else if (type == 4)
		unset(cmd->argv[1]);
	else if (type == 5)
		env(to_write);

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

void pwd(int fd_to_write)
{
	char *cwd;

	cwd = ft_calloc(1024 , sizeof(char));
	if (!cwd)
		return (ft_putstr_fd("an error occured (pwd)\nexiting..\n", 2));
	if (!getcwd(cwd, 1024))
		ft_putstr_fd("error retrieving the current working directory", fd_to_write);
	else
		ft_putstr_fd( cwd, fd_to_write);
	ft_putstr_fd("\n", fd_to_write);
	free(cwd);
}


/* can manage :
 *
 * >echo message
 * >message
 *k
 *>echo -n message
 * message >
 *
 * >echo  message1          message2
 * >message1 message2
 *
 * */
void	echo(char **argv, int to_write)
{
	int 	option_n;
	int i;

	if (!argv[1])
		return;
	option_n = ft_strequ(argv[1], "-n");
	i = 1 + option_n;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], to_write);
		if (argv[i + 1])
			ft_putstr_fd(" ", to_write);
		i++;
	}
	if (!option_n)
		ft_putstr_fd("\n", to_write);
}

/**
 * DO NOT FREE THE RETURN VALUE
 * @param var_name
 * @return value of the variable <varname> in environment
 */
char *get_env_var_value(char *var_name)
{
	int		i;
	t_str_list	*curr;

	i = 0;
	curr = envp_lst;
	if (!var_name || !envp_lst)
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

void export(char **argv, int to_write)
{
	if (!envp_lst)
		return;
	t_str_list *curr = envp_lst;
	if (!argv[1]){
		return ;
	}
	while(curr->next && ft_strcmp(argv[1], curr->next->content) > 0)
		(curr) = (curr)->next;
	t_str_list *tmp = curr->next;
	curr->next = (t_str_list *)ft_lstnew(argv[1]);
	curr->next->next = tmp;
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

void unset(char *var_to_unset)
{

	if (!var_to_unset)
		return((void)0);
	var_to_unset = ft_strjoin(var_to_unset, "=");
	t_str_list *curr = envp_lst;
	if (str_starts_with(curr->content, var_to_unset))
	{
		envp_lst = envp_lst->next;
		ft_lstdelone((t_list *)curr, free);
		return ;
	}
	while (curr && curr->next && \
	!str_starts_with(curr->next->content, var_to_unset))
		curr = curr->next;
	if(curr->next)
	{
		t_str_list *tmp = curr->next->next;
		ft_lstdelone((t_list *)curr->next, free);
		curr->next = tmp;
	}
}

//todo handle -i arg
void env(int to_write)
{
	int i = 0;
	t_str_list *curr;

	curr = envp_lst;
	while (curr)
	{
		ft_putstr_fd((char *)curr->content, to_write);
		ft_putstr_fd("\n", to_write);
		curr = curr->next;
	}
}


void update_pwd(const char *dir)
{

	char * path;
	char *dir_w_slash;
	char * path_tmp =ft_calloc(1024, sizeof (char));

	if (!path_tmp || (!envp_lst && (free(path_tmp), 1)) )
	{
		ft_putstr_fd("an error occurred (!envp_lst || !path_tmp)\nexiting..\n", 2);
		exit(EXIT_FAILURE);
	}
	path_tmp = getcwd(path_tmp, 1024);
	if (!path_tmp)
		return  (ft_putstr_fd("an error occurred (!path_tmp)\n", 2));
	dir_w_slash = ft_strjoin("//", dir);
	path = ft_strjoin(path_tmp, dir_w_slash);
	if (!path)
		return  (ft_putstr_fd("an error occurred (!path)\n", 2));
	if (chdir(path) != 0)
	{
		perror("chdir() error");
		exit(EXIT_FAILURE);
	}
	return (free(path),	free(dir_w_slash),	free(path_tmp));
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
		update_pwd((const char *) dir);
	else
		ft_printf("turboshell: cd: %s: Permission denied\n", dir);
}