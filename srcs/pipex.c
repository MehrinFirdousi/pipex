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

int	redirect_file(char *file_name, int pipe_end, int write)
{
	int	file;

	if (!write)
		file = open(file_name, O_RDONLY, 0777);
	else
		file = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (file == -1)
	{
		perror(file_name);
		close(file);
		return (0);
	}
	dup2(file, pipe_end);
	close(file);
	return (1);
}

t_alloced	set_alloc(int p1[], int p2[], char **cmd, char *path)
{	
	t_alloced	mem;

	mem.pipes[0][0] = p1[0];
	mem.pipes[0][1] = p1[1];
	mem.pipes[1][0] = p2[0];
	mem.pipes[1][1] = p2[1];
	mem.cmd = cmd;
	mem.path = path;
	return (mem);
}

t_alloced	check_cmd(int p1[], int p2[], char *cmd_str, char **envp)
{
	char		**cmd;
	char		*path_name;
	t_alloced	mem_to_free;

	if (!cmd_str || !cmd_str[0])
			exit_msg("pipex", EMPTY_STRING_ERR, 2, set_alloc(p1, p2, 0, 0));
		cmd = ft_split(cmd_str, ' ');
		if (!cmd || !cmd[0])
			exit_msg(cmd_str, CMD_ERR, 127, set_alloc(p1, p2, 0, 0));
		path_name = get_pathname(cmd[0], envp);
		mem_to_free = set_alloc(p1, p2, cmd, path_name);
		if (!path_name && access(cmd[0], F_OK) == 0)
			path_name = ft_strdup(cmd[0]);
		else if (!path_name)
			exit_msg(cmd[0], CMD_ERR, 127, mem_to_free);
		if (access(path_name, X_OK) != 0)
			exit_msg(cmd[0], PERMISSION_ERR, 126, mem_to_free);
	return (mem_to_free);
}

int	exec_cmd(int p1[], int p2[], char *cmd_str, char **envp)
{
	int			pid;
	t_alloced	c;

	pid = check_err("fork", fork());
	if (pid == 0)
	{	
		close(p2[0]);
		c = check_cmd(p1, p2, cmd_str, envp);
		dup2(p1[0], STDIN_FILENO);
		close(p1[0]);
		dup2(p2[1], STDOUT_FILENO);
		close(p2[1]);
		check_err("execve", execve(c.path, c.cmd, envp));
	}
	close(p1[0]);
	close(p2[1]);
	return (pid);
}

int	main(int argc, char**argv, char**envp)
{
	int	p[2][2];
	int	status;
	int	i;
	int	pid[2];

	if (argc != 5)
	{
		ft_printf("pipex: Incorrect number of arguments\n");
		exit(2);
	}
	i = -1;
	check_err("pipe", pipe(p[0]));
	while (++i < 2)
	{
		check_err("pipe", pipe(p[!i]));
		close(p[0][!i]);
		if (redirect_file(argv[i * 3 + 1], p[0][i], i))
			pid[i] = exec_cmd(p[i], p[!i], argv[i + 2], envp);
	}
	i = -1;
	while (++i < 2)
		waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

// int	main(int argc, char**argv, char**envp)
// {
// 	int	p[2][2];
// 	int	open_flags;
// 	int	status;
// 	int	i;
// 	int	pid;

// 	if (argc != 5)
// 	{
// 		ft_printf("pipex: Incorrect number of arguments\n");
// 		exit(2);
// 	}
// 	i = 1;
// 	check_err2("pipe", pipe(p[0]), set_alloc(p[0], p[1], 0, 0));
// 	i += redirect_file(argv[1], p[0][0], O_RDONLY);
// 	close(p[0][1]);
// 	open_flags = O_WRONLY | O_TRUNC | O_CREAT;
// 	while (argv[++i + 2])
// 	{
// 		check_err2("pipe", pipe(p[!(i & 1)]), set_alloc(p[0], p[1], 0, 0));
// 		if (!argv[i + 2])
// 			if (redirect_file(argv[argc - 1], p[!(i & 1)][1], open_flags))
// 				break ;
// 		pid = exec_cmd(p[i & 1], p[!(i & 1)], argv[i], envp);
// 	}
// 	close(p[i & 1][0]);
// 	i = -1;
// 	while (++i < argc - 3)
// 		if (wait(&status) == pid && WIFEXITED(status))
// 			exit(WEXITSTATUS(status));
// 	return (0);
// }

	// check_err2("pipe", pipe(p[1]), set_alloc(p[0], p[1], 0, 0));
	// close(p[0][1]);
	// if (redirect_file(argv[1], p[0][0], O_RDONLY))
	// 	pid[0] = exec_cmd(p[0], p[1], argv[2], envp);
	
	// check_err2("pipe", pipe(p[0]), set_alloc(p[0], p[1], 0, 0));
	// close(p[0][0]);
	// if (redirect_file(argv[4], p[0][1], O_WRONLY | O_TRUNC | O_CREAT))
	// 	pid[1] = exec_cmd(p[1], p[0], argv[3], envp);