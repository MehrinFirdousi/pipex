/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:19:02 by mfirdous          #+#    #+#             */
/*   Updated: 2022/08/23 18:19:02 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifdef _WIN32 /* remove WIN macros for submission */
#  include <io.h>
#  define STDIN_FILENO 0
#  define STDOUT_FILENO 1
#  define F_OK 0
#  define X_OK 1

# else
#  include <unistd.h>
#  include <sys/wait.h>

# endif

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include  <errno.h>
# include "libft.h"

typedef struct s_alloced
{
	int		pipes[2][2];
	char	**cmd;
	char	*path;
}	t_alloced;

# define EMPTY_STRING_ERR	"Command cannot be an empty string"
# define CMD_ERR			"command not found"
# define PERMISSION_ERR		"permission denied"

char	**parse_path(char **envp);
char	*get_pathname(char *cmd_name, char **envp);
int		redirect_file(char *file_name, int pipe_end, int open_flags);
void	free_strs(char **args, char *str, int index);
int		exec_cmd(int p1[], int p2[], char *cmd_str, char **envp);
int		check_err(char *func_name, int ret_value);
int		check_err2(char *func_name, int ret_value, t_alloced mem);
void	exit_msg(char *heading, char *error_msg, int error_code, t_alloced mem);

#endif