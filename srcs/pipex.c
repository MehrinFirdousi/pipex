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

int	redirect_file(char *file_name, int pipe_end, int open_flags)
{
	int	file;

	file = open(file_name, open_flags, 0777);
	if (file == -1)
	{
		perror(file_name);
		close(file);
		return (1);
	}
	dup2(file, pipe_end);
	close(file);
	return (0);
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

int	exec_cmd(int p1[], int p2[], char *cmd_str, char **envp)
{
	char		**cmd;
	char		*path_name;
	t_alloced	mem_to_free;
	int			pid;

	pid = check_err("fork", fork());
	if (pid == 0)
	{	
		if (!cmd_str[0])
			exit_msg("pipex", EMPTY_STRING_ERR, 2, set_alloc(p1, p2, 0, 0));
		cmd = ft_split(cmd_str, ' ');
		path_name = get_pathname(cmd[0], envp);
		mem_to_free = set_alloc(p1, p2, cmd, path_name);
		if (!path_name && access(cmd[0], F_OK) == 0)
			path_name = ft_strdup(cmd[0]);
		else if (!path_name)
			exit_msg(cmd[0], CMD_ERR, 127, mem_to_free);
		if (access(path_name, X_OK) != 0)
			exit_msg(cmd[0], PERMISSION_ERR, 126, mem_to_free);
		dup2(p1[0], STDIN_FILENO);
		close(p1[0]);
		dup2(p2[1], STDOUT_FILENO);
		close(p2[1]);
		check_err("execve", execve(path_name, cmd, envp));
	}
	close(p1[0]);
	close(p2[1]);
	return (pid);
}

int	main(int argc, char**argv, char**envp)
{
	int	p[2][2];
	int	open_flags;
	int	status;
	int	i;
	int	pid;

	if (argc != 5)
	{
		ft_printf("pipex: Incorrect number of arguments\n");
		exit(2);
	}
	i = 1;
	check_err2("pipe", pipe(p[0]), set_alloc(p[0], p[1], 0, 0));
	i += redirect_file(argv[1], p[0][0], O_RDONLY);
	close(p[0][1]);
	open_flags = O_WRONLY | O_TRUNC | O_CREAT;
	while (argv[++i + 1])
	{
		check_err2("pipe", pipe(p[!(i & 1)]), set_alloc(p[0], p[1], 0, 0));
		if (!argv[i + 2])
			if (redirect_file(argv[argc - 1], p[!(i & 1)][1], open_flags))
				break ;
		pid = exec_cmd(p[i & 1], p[!(i & 1)], argv[i], envp);
	}
	close(p[i & 1][0]);
	i = -1;
	while (++i < argc - 3)
		if (wait(&status) == pid && WIFEXITED(status))
			exit(WEXITSTATUS(status));
	return (0);
}
