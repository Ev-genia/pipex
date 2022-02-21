# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 15:05:06 by mlarra            #+#    #+#              #
#    Updated: 2022/02/21 19:15:46 by mlarra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

SRCS_DIR	=	src

SRCS	=	pipex.c

SOURCES	=	${addprefix ${SRCS_DIR}/, ${SRCS}}

OBJ_DIR	=	objects

OBJ		=	${addprefix ${OBJ_DIR}/, ${SRCS:.c=.o}}

HEADER	=	${SRCS_DIR}/pipex.h

CFLAGS	=	-Wall -Wextra -Werror -g

CC		=	gcc

RM		=	rm -f

.PHONY	:	all	clean	fclean	re	bonus norm

${OBJ_DIR}/%.o	: %.c ${HEADER}
	mkdir ${OBJ_DIR} 2> /dev/null || true
	${CC} ${CFLAGS} -c $< -o $@

${NAME}	:	${HEADER} ${OBJ}
	${CC} ${CFLAGS} ${SRCS} -o ${NAME}

all		:	${NAME}

clean	:
	${RM} ${OBJ}
	rmdir ${OBJ_DIR} 2> /dev/null || true

fclean	:	clean
	${RM} ${NAME}

re		:	fclean	all

# bonus	:

norm	:
	norminette ${SRCS}
	norminette ${HEADER}