# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/01 17:34:11 by mfirdous          #+#    #+#              #
#    Updated: 2022/09/03 00:44:04 by mfirdous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# maybe do gcc with libft 

SRCS	=	srcs/pipex.c srcs/pipex_utils.c

B_SRCS	=	srcs/pipex_bonus.c srcs/pipex_utils.c 

OBJS	=	${SRCS:.c=.o}

B_OBJS	=	${B_SRCS:.c=.o}

HEADER	=	include

NAME	=	pipex

LIBFT	=	libft/libft.a

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra -I ${HEADER}

.c.o:		
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 

${NAME}:	${LIBFT} ${OBJS}
			${CC} ${OBJS} ${LIBFT} -o ${NAME}

${LIBFT}:	
			${MAKE} -C libft
			
all:		${NAME}

bonus:		${LIBFT} ${B_OBJS}
			${CC} ${B_OBJS} ${LIBFT} -o ${NAME}

clean:	
			rm -f ${OBJS}
			rm -f ${B_OBJS}
			${MAKE} -C libft clean

fclean:		clean
			rm -f ${NAME}
			${MAKE} -C libft fclean

re:			fclean all

.PHONY:		all clean fclean re bonus