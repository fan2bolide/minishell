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

void cd(struct s_cmd *cmd)
{
	struct stat st;
	char 		*dir;

	dir = cmd->argv[1];
	if (!dir)
		return ;
	if (stat(dir, &st) < 0)
		return(perror("turboshell: cd:"), (void)0);
	if ((st.st_mode & S_IFMT) != S_IFDIR)
		return(ft_printf("turboshell: cd: %s: Not a directory\n", dir), (void)0);
	if (st.st_mode & S_IRUSR)
		update_pwd((const char *) dir);
	else
		ft_printf("turboshell: cd: %s: Permission denied\n", dir);
}