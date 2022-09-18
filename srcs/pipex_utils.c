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

// Returns a list of each colon-separated directory name as an array of strings
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
	if (args)
	{
		while (args[index])
			free(args[index++]);
		free(args);
	}
	if (str)
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

int	check_err2(char *func_name, int ret_value, t_alloced mem)
{
	int	i;

	i = -1;
	if (ret_value == -1)
	{
		perror(func_name);
		while (++i < 2)
		{
			if (mem.pipes[i][i])
				close(mem.pipes[i][i]);
			if (mem.pipes[i][!i])
				close(mem.pipes[i][!i]);
		}
		free_strs(mem.cmd, mem.path, 0);
		exit(EXIT_FAILURE);
	}
	// if (!mem.cmd)
	// 	printf("cmd is null\n");
	// if (!mem.path)
	// 	printf("path is null\n");dd
	return (ret_value);
}

void	exit_msg(char *heading, char *error_msg, int error_code, t_alloced mem)
{
	int	i;

	i = -1;
	ft_printf("%s: %s\n", heading, error_msg);
	while (++i < 2)
	{
		if (mem.pipes[i][i])
			close(mem.pipes[i][i]);
		if (mem.pipes[i][!i])
			close(mem.pipes[i][!i]);
	}
	free_strs(mem.cmd, mem.path, 0);
	exit(error_code);
}

// Returns the command file path if found in PATH, NULL if file does not exist
char	*get_pathname(char *cmd_name, char **envp)
{
	char	*path_name;
	char	*file_name;
	char	**paths;
	int		i;

	paths = parse_path(envp);
	file_name = ft_strjoin("/", cmd_name);
	i = -1;
	while (paths[++i])
	{
		path_name = ft_strjoin(paths[i], file_name);
		if (access(path_name, F_OK) == 0)
			break ;
		free(path_name);
		free(paths[i]);
		path_name = 0;
	}
	free_strs(paths, file_name, i);
	return (path_name);
}
