//
// Created by Aurelien Levra on 29/03/2023.
//

#include "builtins.h"

static void update_pwd();

int user_has_read_permission(struct stat *file_status);

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
	struct stat file_status;
	char 		*dir;
	int const success = 0;
	int const cd_error_code = 1;

	dir = cmd->argv[1];
	if (!dir)
		return ;
	if (get_file_status(dir, &file_status) != success){
		perror("Turboshell :cd");
		update_exit_code(1);
		return ;
	}
	if (!is_a_dir(&file_status)) {
		ft_putstr_fd("Turboshell : cd : not a directory\n", 2);
		update_exit_code(cd_error_code);
		return ;
	}
	if (user_has_read_permission(&file_status))
	{
		if (chdir(dir) != success)
		{
			perror("chdir() error");
			update_exit_code(cd_error_code);
		}
		update_pwd();
		return ;
	}
	else
	{
		print_error(perm_denied, dir);
		update_exit_code(cd_error_code);
		return ;
	}
}

int	user_has_read_permission(struct stat *file_status)
{
	return (*file_status).st_mode & S_IRUSR;
}

bool	is_a_dir(struct stat *file_status)
{
	return ( (*file_status).st_mode & S_IFMT) == S_IFDIR;
}

int	get_file_status (char * file_or_dir, struct stat *result)
{
	return (stat(file_or_dir, result));
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