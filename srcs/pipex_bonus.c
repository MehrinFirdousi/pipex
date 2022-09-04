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
				break;
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

int main(int argc, char**argv, char**envp)
{	
	int		pipes[2][2];
	int		open_flags;
	int		i;
	int		j;

	check_err("pipe", pipe(pipes[0]));
	open_flags = check_heredoc(argv, pipes[0], &i);
	check_err("close", close(pipes[0][1]));
	j = 0; // at any time, this value will be either 0 or 1 and it determines which pipe (pipes[0] or pipes[1]) is to be read from next
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
*/