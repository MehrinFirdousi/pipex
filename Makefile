# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/01 17:34:11 by mfirdous          #+#    #+#              #
#    Updated: 2022/09/01 20:58:03 by mfirdous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# maybe do gcc with libft 

SRCS	=	srcs/pipex.c srcs/pipex_utils.c

B_SRCS	=	srcs/pipex_bonus.c srcs/pipex_utils_bonus.c

OBJS	=	${SRCS:.c=.o}

B_OBJS	=	${B_SRCS:.c=.o}

HEADER	=	includes

NAME	=	pipex

${NAME}:	${OBJS}
			${MAKE} -C libft
			cp libft/libft.a .
			
all:	${NAME}

