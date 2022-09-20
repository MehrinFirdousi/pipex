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

int	check_heredoc(char **argv, int pipe[], int *i)
{
	char	*line;
	int		d_len;

	if (ft_strncmp("here_doc", argv[1], 9) == 0)
	{
		d_len = ft_strlen(argv[2]);
		check_err("write", write(STDOUT_FILENO, "> ", 2));
		while ((line = get_next_line(STDIN_FILENO)))
		{
			if (!ft_strncmp(line, argv[2], d_len) && !line[d_len + 1])
				break ;
			check_err("write", write(pipe[1], line, ft_strlen(line)));
			check_err("write", write(STDOUT_FILENO, "> ", 2));
			free(line);
		}
		*i = 2;
		free(line);
		return (O_WRONLY | O_APPEND | O_CREAT);
	}
	*i = 1;
	redirect_file(argv[1], pipe[0], O_RDONLY);
	return (O_WRONLY | O_TRUNC | O_CREAT);
}

int	main(int argc, char**argv, char**envp)
{	
	int		pipes[2][2];
	int		open_flags;
	int		i;
	int		j;

	check_err("pipe", pipe(pipes[0]));
	open_flags = check_heredoc(argv, pipes[0], &i);
	check_err("close", close(pipes[0][1]));
	j = 0;
	while (argv[++i + 1])
	{
		check_err("pipe", pipe(pipes[!j]));
		if (!argv[i + 2])
			redirect_file(argv[argc - 1], pipes[!j][1], open_flags);
		exec_cmd(pipes[j], pipes[!j], argv[i], envp);
		j = !j;
	}
	check_err("close", close(pipes[j][0]));
	return (0);
}

/* TODO:
	1. remove redirect_file and add the content inline 
	2. error proof check_heredoc
	3. make check_heredoc write to a temporary file instead of the pipe directly because pipe has a limited buffer size
!!! 4. check for leaks if the program returns unexpectedly through an error 
	5. remove free_strs
	6. remove gnl header file from srcs and ask around about making the functions static
	7. return error codes that the real bash pipe returns 

	move error check functions
	clean up bonus main
	test infile and outfile permissions (lag)
	leaks, fds, trace children, track zombies
	
*/