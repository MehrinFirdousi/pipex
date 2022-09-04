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

int	main(int argc, char**argv, char**envp)
{	
	int		pipes[2][2];
	int		open_flags;
	int		i;

	check_err("pipe", pipe(pipes[0]));
	redirect_file(argv[1], pipes[0][0], O_RDONLY);
	check_err("close", close(pipes[0][1]));
	open_flags = O_WRONLY | O_TRUNC | O_CREAT;
	i = 1;
	while (argv[++i + 1])
	{
		check_err("pipe", pipe(pipes[!(i & 1)]));
		if (!argv[i + 2])
			redirect_file(argv[argc - 1], pipes[!(i & 1)][1], open_flags);
		exec_cmd(pipes[i & 1], pipes[!(i & 1)], argv[i], envp);
	}
	check_err("close", close(pipes[i & 1][0]));
	return (0);
}
