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
char **parse_path(char **envp)
{
	char path_var[5];
	int i;

	i = -1;
	while (envp[++i])
	{
		ft_strlcpy(path_var, envp[i], 5);
		if (ft_strncmp(path_var, "PATH", 4) == 0)
			return (ft_split(envp[i] + 5, ':'));
	}
	return (0);
}

void free_strs(char **args, char *str, int index)
{
	while (args[index])
		free(args[index++]);
	free(args);
	free(str);
}

int check_err(char *func_name, int ret_value)
{
	if (ret_value == -1)
	{
		perror(func_name);
		exit(EXIT_FAILURE);
	}
	return (ret_value);
}

// Checks if the cmd file exists in one of the PATH directories and returns the path, NULL if file does not exist
char *get_pathname(char *cmd_name, char **envp)
{
	char *path_name;
	char *file_name;
	char **paths;
	int i;

	paths = parse_path(envp);
	file_name = ft_strjoin("/", cmd_name);
	i = -1;
	while (paths[++i])
	{
		path_name = ft_strjoin(paths[i], file_name);
		if (access(path_name, F_OK) != -1) // maybe also check if file is executable?
			break;
		free(path_name);
		free(paths[i]);
		path_name = 0;
	}
	if (!path_name)
		check_err(cmd_name, -1);
	free_strs(paths, file_name, i);
	return (path_name); // file not found
}

// read from p1, execute command and write its output to p2
void exec_cmd(int p1[], int p2[], char *file, char **cmd, char **env)
{
	int status;

	if (check_err("fork", fork()) == 0)
	{
		check_err("dup2", dup2(p1[0], STDIN_FILENO));
		check_err("close", close(p1[0]));
		check_err("dup2", dup2(p2[1], STDOUT_FILENO));
		check_err("close", close(p2[1]));
		check_err("execve", execve(file, cmd, env));
	}
	check_err("wait", wait(&status));
	if (!WIFEXITED(status)) // maybe remove
		exit(EXIT_FAILURE);
	check_err("close", close(p1[0])); // child done reading
	check_err("close", close(p2[1])); // child done writing, ready for next proc to read
}