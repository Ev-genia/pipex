# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 15:05:06 by mlarra            #+#    #+#              #
#    Updated: 2022/03/02 11:23:55 by mlarra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

SRCS_DIR	=	src

SRCS	=	pipex.c	ft_split.c	ft_execve.c	ft_strjoin.c	ft_strncmp.c\
			utils.c

SOURCES	=	${addprefix ${SRCS_DIR}/, ${SRCS}}

OBJ_DIR	=	objects

OBJ		=	${SOURCES:${SRCS_DIR}/%.c=${OBJ_DIR}/%.o}

HEADER	=	${SRCS_DIR}/pipex.h

CFLAGS	=	-Wall -Wextra -Werror -g

CC		=	gcc

RM		=	rm -f

.PHONY	:	all	clean	fclean	re	bonus norm

${OBJ_DIR}/%.o	: ${SRCS_DIR}/%.c ${HEADER}
	@mkdir ${OBJ_DIR} 2> /dev/null || true
	${CC} ${CFLAGS} -c $< -o $@
# @echo "created objects file"

${NAME}	:	${HEADER} ${OBJ}
	${CC} ${CFLAGS} ${SOURCES} -o ${NAME}

all		:	${NAME}

clean	:
	${RM} ${OBJ}
	@rmdir ${OBJ_DIR} 2> /dev/null || true

fclean	:	clean
	${RM} ${NAME}

re		:	fclean	all

# bonus	:

norm	:
	norminette ${SRCS}
	norminette ${HEADER}