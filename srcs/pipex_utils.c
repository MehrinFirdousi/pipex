/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:17:27 by mfirdous          #+#    #+#             */
/*   Updated: 2022/08/23 20:17:27 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Finds PATH environment variable and returns a list of each colon-separated directory in an array of strings
char	**parse_path(char **envp)
{
	char	path_var[5];
	int		i;

	i = -1;
	while (envp[++i])
	{
		ft_strlcpy(path_var, envp[i], 5);
		if (ft_strncmp(path_var, "PATH", 4) == 0)
			return (ft_split(envp[i] + 5, ':'));
	}
	return (0);
}

void	free_strs(char **args, char *str, int index)
{
	while (args[index])
		free(args[index++]);
	free(args);
	free(str);
}

int	check_err(char *func_name, int ret_value)
{
	if (ret_value == -1)
	{
		perror(func_name);
		exit(EXIT_FAILURE);
	}
	return (ret_value);
}

void	exit_msg(char *heading, char *error_msg, int error_code)
{
	ft_printf("%s: %s\n", heading, error_msg);
	exit(error_code);
}

// Checks if the cmd file exists in one of the PATH directories and returns the path, NULL if file does not exist
char	*get_pathname(char *cmd_name, char **envp)
{
	char	*path_name;
	char	*file_name;
	char	**paths;
	int		i;

	// if (!access(cmd_name, X_OK))
	// 	return (cmd_name);
	paths = parse_path(envp);
	file_name = ft_strjoin("/", cmd_name);
	i = -1;
	while (paths[++i])
	{
		path_name = ft_strjoin(paths[i], file_name);
		if (access(path_name, F_OK) == 0) // file found
			break ;
		free(path_name);
		free(paths[i]);
		path_name = 0;
	}
	if (!path_name)
		exit_msg(cmd_name, "command not found", 127);
	if (access(path_name, X_OK) == -1)
		exit_msg(cmd_name, "permission denied", 126);
	free_strs(paths, file_name, i);
	return (path_name);
}

// read from p1, execute command and write its output to p2
void	exec_cmd(int p1[], int p2[], char *cmd_str, char **envp)
{
	char	**cmd;
	char	*path_name;

	cmd = ft_split(cmd_str, ' ');
	if (!cmd || !cmd[0])
		exit_msg(cmd_str, "command not found", 127);
	path_name = get_pathname(cmd[0], envp);
	if (check_err("fork", fork()) == 0)
	{
		check_err("dup2", dup2(p1[0], STDIN_FILENO));
		check_err("close", close(p1[0]));
		check_err("dup2", dup2(p2[1], STDOUT_FILENO));
		check_err("close", close(p2[1]));
		check_err("execve", execve(path_name, cmd, envp));
	}
	free_strs(cmd, path_name, 0);
	check_err("close1", close(p1[0]));
	check_err("close2", close(p2[1]));
}