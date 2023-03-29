
#include "builtins.h"

int check_export_syntax(char **argv);

int is_echos_option_n(char *argv1);
void free_keyval(void *uncasted_keyval);

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
	else if (type == 6)
		exit(EXIT_SUCCESS); // todo replace with exit_code or with argv[1]
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


/**
 * DO NOT FREE THE RETURN VALUE
 * @param var_name
 * @return value of the variable <varname> in environment
 */
char *get_env_var_value(char *var_name)
{
	int		i;
	t_keyval_list	*curr;

	i = 0;
	curr = envp_lst;
	if (!var_name || !envp_lst)
		return NULL;
	while (curr && !ft_strequ(curr->content->key, var_name))
		curr = curr->next;
	if (!curr)
		return (NULL);
	return (curr->content->value);
}

void export(char **argv, int to_write)
{
	if (!envp_lst)
		return;
	t_keyval_list *curr = envp_lst;
	if (check_export_syntax(argv) <= 0)
		return (ft_printf("Bad syntax\n"), (void)(0));
	if (!argv[1])
	{
		while (curr)
		{
			ft_putstr_fd("declare -x ", to_write);
			ft_putstr_fd(curr->content->key, to_write);
			if (curr->content->value)
			{
				ft_putstr_fd("=\"", to_write);
				ft_putstr_fd(curr->content->value, to_write);
				ft_putstr_fd("\"", to_write);
			}
			ft_putstr_fd("\n", to_write);
			curr = curr->next;
		}
		return ;
	}
	t_keyval *keyval_to_export = create_keyval_from_env_var(argv[1]);
	unset(keyval_to_export->key);
	while(curr->next && ft_strcmp(argv[1], curr->next->content->key) > 0)
		(curr) = (curr)->next;
	t_keyval_list *tmp = curr->next;
	curr->next = (t_keyval_list *)ft_lstnew(keyval_to_export);
	curr->next->next = tmp;
}

int check_export_syntax(char **argv)
{
	if (argv[1] == NULL)
		return 1;
	if (isalpha(argv[1][0]) || argv[1][0] == '_')
		return (1);
	return 0;
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
	t_keyval_list *curr = envp_lst;
	if (ft_strequ(curr->content->key, var_to_unset))
	{
		envp_lst = envp_lst->next;
		ft_lstdelone((t_list *)curr, (void (*)(void *))&free_keyval);
		return ;
	}
	while (curr && curr->next && \
	!ft_strequ(curr->next->content->key, var_to_unset))
		curr = curr->next;
	if(curr->next)
	{
		t_keyval_list *tmp = curr->next->next;
		ft_lstdelone((t_list *)curr->next, free);
		curr->next = tmp;
	}
}

void free_keyval(void *uncasted_keyval) {
	t_keyval *keyval = uncasted_keyval;

	ft_printf("(free keyval..)\n"); //debug
	ft_printf("keyval->key : %s\n", keyval->key);
	ft_printf("keyval->val : %s\n", keyval->value);

	free(keyval->key);
	free(keyval->value);

	ft_printf("keyval->key : %s\n", keyval->key);
	ft_printf("keyval->val : %s\n", keyval->value);
	ft_printf("(exiting free keyval..)\n");

}

void env(int to_write)
{
	int i = 0;
	t_keyval_list *curr;

	curr = envp_lst;
	if (curr)
		curr = curr->next; //skipping the first value (exit code)
	while (curr && curr->content)
	{
		if (curr->content->value)
		{
			ft_putstr_fd(curr->content->key, to_write);
			ft_putstr_fd("=", to_write);
			ft_putstr_fd(curr->content->value, to_write);
			ft_putstr_fd("\n", to_write);
		}
		curr = curr->next;
	}
}



