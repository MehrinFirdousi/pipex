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

void redirect_file(char *file_name, int pipe_end, int open_flags)
{
	int file;

	check_err(file_name, file = open(file_name, open_flags, 0777));
	check_err("dup2", dup2(file, pipe_end));
	check_err("close", close(file));
}

int main(int argc, char**argv, char**envp)
{	
	int pipes[2][2];
	char **cmd;
	char *path_name;
	int i;
	
	// if (argc < 4)
	// 	return (0);
	check_err("pipe", pipe(pipes[0]));
	redirect_file(argv[1], pipes[0][0], O_RDONLY);
	check_err("close", close(pipes[0][1]));
	i = 1;
	while (argv[++i + 1])
	{
		cmd = ft_split(argv[i], ' ');
		path_name = get_pathname(cmd[0], envp);
		check_err("pipe", pipe(pipes[!(i & 1)]));
		if (argv[i + 2] == 0)
			redirect_file(argv[i + 1], pipes[!(i & 1)][1], O_WRONLY | O_TRUNC | O_CREAT);
		exec_cmd(pipes[i & 1], pipes[!(i & 1)], path_name, cmd, envp);	// read from p1 and write to p2 (Parent 1>==p1==>0 Child 1>==p2==>0 Parent)
		free_strs(cmd, path_name, 0);
	}
	check_err("close", close(pipes[i & 1][0]));
	return (0);
}