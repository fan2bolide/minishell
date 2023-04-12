/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienlevra <aurelienlevra@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 01:46:39 by aurelienlev       #+#    #+#             */
/*   Updated: 2023/04/12 01:47:25 by aurelienlev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			check_export_syntax(char **argv);
int			is_echos_option_n(char *argv1);
void		free_keyval(void *uncasted_keyval);
void		insert_env_var(t_keyval *keyval_to_insert);
void		update_env_var(t_keyval *keyval_to_update);
bool		env_var_exist(t_keyval *keyval_to_check);
void		shell_exit(t_cmd_list **cmd);
bool		check_numeric_argument(char *argv1);

void	exec_builtin(t_cmd_list **cmd_list_ptr, int to_write)
{
	int		type;
	t_cmd	*cmd;

	cmd = (*cmd_list_ptr)->content;
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
		shell_exit(cmd_list_ptr);
}

void	shell_exit(t_cmd_list **cmd_list_ptr)
{
	int			exit_code_modulo;
	const char	*exit_code;
	t_cmd		*cmd;
	char		*argv1;

	cmd = (*cmd_list_ptr)->content;
	argv1 = cmd->argv[1];
	ft_printf("exit\n");
	exit_code = envp_lst->content->value;
	exit_code_modulo = ft_atoi(exit_code) % 256;
	ft_lstclear((t_list **)&envp_lst, &destroy_keyval);
	if (!argv1)
	{
		ft_lstclear((t_list **)cmd_list_ptr, (void (*)(void *)) & destroy_cmd);
		exit(exit_code_modulo);
	}
	if (check_numeric_argument(argv1) == false)
	{
		print_error(numeric_argument_required, ft_strjoin_secure("exit: ", argv1));
		exit(255);
	}
	exit_code_modulo = ft_atoll(argv1) % 256;
	ft_lstclear((t_list **)cmd_list_ptr, (void (*)(void *)) & destroy_cmd);
	exit(exit_code_modulo);
}

bool	check_numeric_argument(char *argv1)
{
	if (!can_be_converted_to_long(argv1))
		return (false);
	if (argv1[0] == '-')
		argv1++;
	if (!str_contains_digits_only(argv1))
		return (false);
	return (true);
}


// returns -1 if str is not a builtins
// returns [0...6] if str is builtins
int	is_builtin(char *str)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int			i;

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
char	*get_env_var_value(char *var_name)
{
	t_keyval_list	*curr;

	curr = envp_lst;
	if (!var_name || !envp_lst)
		return (NULL);
	while (curr && !ft_strequ(curr->content->key, var_name))
		curr = curr->next;
	if (!curr)
		return (NULL);
	return (curr->content->value);
}

/**
 * @param var_name
 * @return keyval of <varname> in environment
 */
t_keyval	*get_env_var(char *var_name)
{
	t_keyval_list	*curr;

	curr = envp_lst;
	if (!var_name || !envp_lst)
		return (NULL);
	while (curr && !ft_strequ(curr->content->key, var_name))
		curr = curr->next;
	if (!curr)
		return (NULL);
	return (curr->content);
}

/**
 * @param var_name
 */
void	set_env_var_value(char *var_key, char *var_value)
{
	t_keyval	*var_to_set;

	if (!var_key)
		return (print_error(error_occured, "set_env_var_value"));
	var_to_set = get_env_var(var_key);
	if (var_to_set)
		free(var_to_set->value);
	if (!var_to_set)
	{
		var_to_set = create_keyval();
		var_to_set->key = ft_strdup(var_key);
		insert_or_update_env_var(var_to_set);
	}
	var_to_set->value = ft_strdup(var_value);
	if (!var_to_set->value)
		print_error(error_occured, "set_env_var_value");
}

/**
 * insert env_var in ascii order
 * if env_var already exist,
	update the value and free the keyval given in parameter
 * @param keyval_to_insert
 */
void	insert_or_update_env_var(t_keyval *keyval_to_insert)
{
	if (!keyval_to_insert)
		return ;
	if (env_var_exist(keyval_to_insert))
		update_env_var(keyval_to_insert);
	else
		insert_env_var(keyval_to_insert);
}

bool	env_var_exist(t_keyval *keyval_to_check)
{
	t_keyval_list	*curr;

	if (envp_lst)
		curr = envp_lst->next;
	if (!envp_lst || !curr)
		return (0);
	while (curr && !ft_strequ(keyval_to_check->key, curr->content->key))
		curr = curr->next;
	if (!curr)
		return (0);
	return (1);
}

void	update_env_var(t_keyval *keyval_to_update)
{
	t_keyval_list	*curr;

	if (envp_lst)
		curr = envp_lst->next;
	if (!envp_lst || !curr)
		return ;
	while (!ft_strequ(keyval_to_update->key, curr->content->key))
		curr = curr->next;
	if (keyval_to_update->value)
	{
		free(curr->content->value);
		curr->content->value = ft_strdup(keyval_to_update->value);
		if (!curr->content->value)
			print_error(error_occured, "update_env_var");
	}
	free_keyval(keyval_to_update);
	free(keyval_to_update);
}

void	insert_env_var(t_keyval *keyval_to_insert)
{
	t_keyval_list	*curr;
	t_keyval_list	*tmp;

	curr = NULL;
	if (envp_lst)
		curr = envp_lst->next;
	if (!curr || !envp_lst)
		return (print_error(error_occured, "insert_env_var"), (void)0);
	while (curr->next && ft_strcmp(keyval_to_insert->key,
			curr->next->content->key) > 0)
		(curr) = (curr)->next;
	tmp = curr->next;
	curr->next = (t_keyval_list *)ft_lstnew(keyval_to_insert);
	curr->next->next = tmp;
}

void	export(char **argv, int to_write)
{
	t_keyval_list	*curr;
	t_keyval		*keyval_to_export;

	if (!envp_lst)
		return ;
	curr = envp_lst;
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
	keyval_to_export = create_keyval_from_env_var(argv[1]);
	if (!keyval_to_export)
		return (print_error(error_occured, "export"));
	insert_or_update_env_var(keyval_to_export);
}

int	check_export_syntax(char **argv)
{
	if (argv[1] == NULL)
		return (1);
	if (isalpha(argv[1][0]) || argv[1][0] == '_')
		return (1);
	return (0);
}

void	unset(char *var_to_unset)
{
	t_keyval_list	*curr;
	t_keyval_list	*tmp;

	if (!var_to_unset)
		return ((void)0);
	curr = envp_lst;
	if (ft_strequ(curr->content->key, var_to_unset))
	{
		envp_lst = envp_lst->next;
		ft_lstdelone((t_list *)curr, (void (*)(void *)) & free_keyval);
		return ;
	}
	while (curr && curr->next && \
			!ft_strequ(curr->next->content->key, var_to_unset))
		curr = curr->next;
	if (curr->next)
	{
		tmp = curr->next->next;
		ft_lstdelone((t_list *)curr->next, &destroy_keyval);
		curr->next = tmp;
	}
}

void	free_keyval(void *uncasted_keyval)
{
	t_keyval	*keyval;

	keyval = uncasted_keyval;
	free(keyval->key);
	free(keyval->value);
}

void	env(int to_write)
{
	t_keyval_list	*curr;

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
