/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 02:59:28 by bajeanno          #+#    #+#             */
/*   Updated: 2023/03/01 20:32:28 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:30:13 by alevra            #+#    #+#             */
/*   Updated: 2023/03/01 23:33:32 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//shall NOT be submitted in the vogosphere
//do NOT try to norm this file
//for debug purpose only

void	log_cmd(t_cmd *cmd);
//debug
void	log_token(t_token *token)
{
	ft_printf("content\t: %s\n", token->content);
	ft_printf("type\t: ");
	switch (token->type)
	{
		case 0:
			ft_printf("error");
			break ;
		case exec_name:
			ft_printf("exec_name");
			break ;
		case arg:
			ft_printf("arg");
			break ;
		case file:
			ft_printf("file");
			break ;
		case operator_pipe:
			ft_printf("operator_pipe");
			break ;
		case redirect_in:
			ft_printf("redirect_in");
			break ;
		case redirect_out_trunc:
			ft_printf("redirect_out_trunc");
			break ;
		case redirect_hd:
			ft_printf("redirect_hd");
			break ;
		case redirect_out_append:
			ft_printf("redirect_out_append");
			break ;
	}
	ft_printf("\n\n");
}

//debug
void	log_token_list(t_list *token_list)
{
	t_token	*token_ptr;
	t_list	*token_list_cursor;

	token_ptr = (t_token *)token_list->content;
	log_token(token_ptr);
	token_list_cursor = token_list->next;
	while (token_list_cursor)
	{
		token_ptr = (t_token *)token_list_cursor->content;
		log_token(token_ptr);
		token_list_cursor = token_list_cursor->next;
	}
}

//debug
void	log_cmd_lst(t_list *cmd_list)
{
	t_cmd	*current_cmd;
	int         node;

	node = 0;
	if (!cmd_list)
		return (ft_printf("log_cmd_lst failed (NULL pointer)\n"), (void)0);
	current_cmd = cmd_list->content;
	while(cmd_list)
	{
		ft_printf("node %d\n", node++);
		log_cmd(current_cmd);
		cmd_list = cmd_list->next;
		if (cmd_list)
			current_cmd = cmd_list->content;
	}
}

//debug
void	log_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return (ft_printf("log_cmd failed (NULL pointer)\n"), (void)0);
	//debug
	i = 0;
	while (cmd->argv[i] != NULL)
	{
		ft_printf("cmd->argv[%d] : %s\n", i, cmd->argv[i]); //debug
		i++;
	}
	ft_printf("cmd->path : %s\n", cmd->path);
	if (cmd->redirect_in)
		ft_printf("cmd->redirect_in : %s\n", cmd->redirect_in);
	if (cmd->redirect_out)
	{
		ft_printf("cmd->redirect_out_trunc : %s\n", cmd->redirect_out);
		ft_printf("cmd->redirect_out_mode : ");
		switch (cmd->redirect_out_mode) {
			case 0:
				ft_printf("none\n");
				break;
			case 1:
				ft_printf("append\n");
				break;
			case 2:
				ft_printf("trunc\n");
				break;
		}

	}
	if (cmd->heredoc_mode)
		ft_printf("here_doc mode !\n");
}

//only for debug purpose
//return the token array for the command " cat file1 | wc"
t_list *get_sample_tokens()
{
	t_list *res;
	t_token *token_array;
	int 	size = 10;

	token_array = malloc(sizeof(t_token) * size);

	token_array[0].content = ft_strdup(">");
	token_array[0].type = redirect_out_trunc;

	token_array[1].content = ft_strdup("file1");
	token_array[1].type = file;

	token_array[2].content = ft_strdup("cat");
	token_array[2].type = exec_name;

	token_array[3].content = ft_strdup("-e");
	token_array[3].type = arg;

	token_array[4].content = ft_strdup("|");
	token_array[4].type = operator_pipe;

	token_array[5].content = ft_strdup("cat");
	token_array[5].type = exec_name;

	token_array[6].content = ft_strdup("-e");
	token_array[6].type = arg;

	token_array[7].content = ft_strdup("-a");
	token_array[7].type = arg;

	token_array[8].content = ft_strdup("<");
	token_array[8].type = redirect_in;

	token_array[9].content = ft_strdup("file2");
	token_array[9].type = file;

	res = ft_lstnew((void *)token_array);


	t_token *tok = NULL;

	ft_printf("\nsample exec_name line : %s ", token_array[0].content); //debug
	for (int i = 1; i < size; i++)
	{
		tok = &token_array[i];
		ft_lstadd_back(&res, ft_lstnew((void *)tok));
		ft_printf(tok->content);
		ft_printf(" ");
	}
	ft_printf("\n");
	return res;
}

//debug
//void	debug_aurel(int argc, char **argv, char **envp)
//{
//	t_list	*token_list;
//
//	if (argc > 1 && ft_strequ(argv[1], "debug") == 1)
//	{
//		token_list = get_sample_tokens();
////		convert_token_lst_into_cmd_lst(token_list); need envp_lst_ptr here
//	}
//}

t_keyval_list	*g_envp_lst;

bool	set_exit_code(void);

char	*prompt(int term_does_handle_color)
{
	char	*res;
	char	*tmp;

	if (!setup_signals(sig_handler_interactive_mode))
		return (NULL);
	if (term_does_handle_color)
	{
		if (get_exit_code())
			tmp = readline(ANSI_RED " \001➜\002 " ANSI_RESET);
		else
			tmp = readline(ANSI_BLUE " \001➜\002 " ANSI_RESET);
	}
	else
		tmp = readline(" ➜ ");
	if (tmp == NULL)
		return (ft_strdup("exit"));
	res = ft_strtrim(tmp, " ");
	free(tmp);
	if (!ft_strequ(res, ""))
		add_history(res);
	if (!setup_signals(sig_handler_execution_mode))
		return (NULL);
	return (res);
}

///converts char *envp to key/value list so we can use and update it
t_keyval_list	*convert_str_arr_into_new_keyval_list(char **array)
{
	t_keyval_list	*res;

	res = (t_keyval_list *)ft_lstnew(NULL);
	if (array == NULL)
		return (res);
	res->content = create_keyval_from_env_var(*array);
	array++;
	while (*array)
	{
		ft_lstadd_back((t_list **)&res,
						ft_lstnew(create_keyval_from_env_var(*array)));
		array++;
	}
	return (res);
}

///assign correct values to global var 'envp_lst'
void	dup_envp(char **envp) //todo si env est NULL, créer ququchose quand même
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
	}
	else
		g_envp_lst = convert_str_arr_into_new_keyval_list(envp);
	if (!set_exit_code())
		return (ft_lstclear((t_list **)&g_envp_lst, destroy_keyval));
}

int	main(int argc, char **argv, char **envp)
{
	char			*prompt_res;
	t_token_list	*token_list;
	t_cmd_list		*cmd_lst;

	(void)argc;
	(void)argv;
	dup_envp(envp);
	while (1)
	{
		prompt_res = prompt(*envp && check_terminal());
		if (!prompt_res)
			return (perror("signal setup failed: "), 1);
		token_list = get_main_token_list(prompt_res);
		free(prompt_res);
		if (!token_list)
			continue ;
		token_list = token_parsing(token_list);
		if (!token_list)
			continue ;
		if (!expand_tokens_from_list(token_list))
			return (0);
		cmd_lst = convert_token_lst_into_cmd_lst((t_token_list *)token_list);
		ft_lstclear((t_list **)&token_list, destroy_token);
		execute_cmd_line(cmd_lst);
	}
}
