//
// Created by Aurelien Levra on 29/03/2023.
//

#include "builtins.h"

static void update_pwd(const char *dir);

void pwd(int fd_to_write)
{
	char *cwd;

	cwd = ft_calloc(1024 , sizeof(char));
	if (!cwd)
		return (ft_putstr_fd("an error occurred (pwd)\nexiting..\n", 2));
	if (!getcwd(cwd, 1024))
		ft_putstr_fd("error retrieving the current working directory", fd_to_write);
	else
		ft_putstr_fd( cwd, fd_to_write);
	ft_putstr_fd("\n", fd_to_write);
	free(cwd);
}

static void update_pwd(const char *dir)
{

	char * path;
	char *dir_w_slash;
	char * path_tmp =ft_calloc(1024, sizeof (char));
	char * path_tmp2 =ft_calloc(1024, sizeof (char));

	if (!path_tmp || !path_tmp2 || (!envp_lst && (free(path_tmp), 1)) )
	{
		ft_putstr_fd("an error occurred (!envp_lst || !path_tmp)\nexiting..\n", 2);
		exit(EXIT_FAILURE);
	}
	path_tmp = getcwd(path_tmp, 1024);
	if (!path_tmp)
		return  (ft_putstr_fd("an error occurred (!path_tmp)\n", 2));
	dir_w_slash = ft_strjoin("/", dir);
	path = ft_strjoin(path_tmp, dir_w_slash);
	if (!path)
		return  (ft_putstr_fd("an error occurred (!path)\n", 2));
	if (chdir(path) != 0)
	{
		perror("chdir() error");
		exit(EXIT_FAILURE);
	}
	path_tmp2 = getcwd(path_tmp2, 1024);
	char *env_var_oldpwd = ft_strjoin_secure("OLDPWD=", path_tmp);
	char *env_var_newpwd = ft_strjoin_secure("PWD=", path_tmp2);
	insert_or_update_env_var(create_keyval_from_env_var(env_var_oldpwd));
	insert_or_update_env_var(create_keyval_from_env_var(env_var_newpwd));
	free(env_var_oldpwd);
	return (free(path),	free(dir_w_slash),	free(path_tmp), free(path_tmp2));
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
		update_pwd((const char *) dir);
		update_exit_code(0);
		return ;
	}
	else
	{
		perror("Turboshell :");
		update_exit_code(errno);
		return ;
	}
}