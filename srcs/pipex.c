/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:57:10 by mfirdous          #+#    #+#             */
/*   Updated: 2022/08/23 18:57:10 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect_file(char *file_name, int pipe_end, int open_flags)
{
	int	file;

	check_err(file_name, file = open(file_name, open_flags, 0777));
	check_err("dup2", dup2(file, pipe_end));
	check_err("close", close(file));
}

t_alloced	set_alloc(int pipes[2][2], char **cmd, char *path)
{	
	t_alloced	mem;

	mem.pipes[0][0] = pipes[0][0];
	mem.pipes[0][1] = pipes[0][1];
	mem.pipes[1][0] = pipes[1][0];
	mem.pipes[1][1] = pipes[1][1];
	mem.cmd = cmd;
	mem.path = path;
	return (mem);
}

void	exec_cmd(int p1[], int p2[], char *cmd_str, char **envp)
{
	char	**cmd;
	char	*path_name;

	if (!cmd_str[0])
		exit_msg("pipex", "Command cannot be an empty string", 2);
	cmd = ft_split(cmd_str, ' ');
	path_name = get_pathname(cmd[0], envp);
	if (!path_name && access(cmd[0], F_OK) == 0)
		path_name = ft_strdup(cmd[0]);
	else if (!path_name)
		exit_msg(cmd[0], "command not found", 127);
	if (access(path_name, X_OK) != 0)
		exit_msg(cmd[0], "permission denied", 126);
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

int	main(int argc, char**argv, char**envp)
{	
	int			pipes[2][2];
	int			open_flags;
	int			status;
	int			i;

	if (argc != 5)
		exit_msg("pipex", "Incorrect number of arguments", 2);
	check_err2("pipe", pipe(pipes[0]), set_alloc(pipes, 0, 0));
	redirect_file(argv[1], pipes[0][0], O_RDONLY);
	check_err2("close", close(pipes[0][1]), set_alloc(pipes, 0, 0));
	open_flags = O_WRONLY | O_TRUNC | O_CREAT;
	i = 1;
	while (argv[++i + 1])
	{
		check_err2("pipe", pipe(pipes[!(i & 1)]), set_alloc(pipes, 0, 0));
		if (!argv[i + 2])
			redirect_file(argv[argc - 1], pipes[!(i & 1)][1], open_flags);
		exec_cmd(pipes[i & 1], pipes[!(i & 1)], argv[i], envp);
	}
	check_err2("close", close(pipes[i & 1][0]), set_alloc(pipes, 0, 0));
	check_err2("wait", wait(&status), set_alloc(pipes, 0, 0));
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	return (0);
}