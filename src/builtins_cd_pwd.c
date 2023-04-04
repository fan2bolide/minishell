//
// Created by Aurelien Levra on 29/03/2023.
//

#include "builtins.h"

static void update_pwd();

void pwd(int fd_to_write)
{
	char *cwd;

	cwd = ft_calloc(1024 , sizeof(char));
	if (!cwd)
		return (print_error(error_occured, "pwd"));
	if (!getcwd(cwd, 1024))
		print_error(cwd_error, "");
	else
		ft_putstr_fd( cwd, fd_to_write);
	ft_putstr_fd("\n", fd_to_write);
	free(cwd);
}

void cd(struct s_cmd *cmd)
{
	struct stat st;
	char 		*dir;

	dir = cmd->argv[1];
	if (!dir)
		return ;
	if (stat(dir, &st) < 0){
		perror("Turboshell :cd");
		update_exit_code(1);
		return ;
	}
	if ((st.st_mode & S_IFMT) != S_IFDIR) {
		perror("Turboshell :cd");
		update_exit_code(1);
		return ;
	}
	if (st.st_mode & S_IRUSR)
	{
		if (chdir(dir) != 0)
		{
			perror("chdir() error");
			update_exit_code(0);
		}
		update_pwd();
		return ;
	}
	else
	{
		print_error(perm_denied, dir);
		update_exit_code(errno);
		return ;
	}
}

static void update_pwd()
{
	char * path =ft_calloc(1024, sizeof (char));
	if (!path)
	{
		print_error(error_occured, "(!envp_lst || !path)");
		exit(EXIT_FAILURE);
	}
	path = getcwd(path, 1024);
	if (!path)
		return  (perror("getcwd"));
	char *env_var_oldpwd = ft_strjoin_secure("OLDPWD=", get_env_var_value("PWD"));
	char *env_var_newpwd = ft_strjoin_secure("PWD=", path);
	insert_or_update_env_var(create_keyval_from_env_var(env_var_oldpwd));
	insert_or_update_env_var(create_keyval_from_env_var(env_var_newpwd));
	free(env_var_oldpwd);
	free(env_var_newpwd);
	return (free(path));

}