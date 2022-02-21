# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 15:05:06 by mlarra            #+#    #+#              #
#    Updated: 2022/02/16 17:16:37 by mlarra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

SRCS	=	pipex.c

# OBJ_DIR	=	obj

# OBJ		=	${addprefix ${OBJ_DIR}/, ${SRCS:.c=.o}}
OBJ		=	${SRCS:.c=.o}

HEADER	=	pipex.h

CFLAGS	=	-Wall -Wextra -Werror -g

CC		=	gcc

RM		=	rm -f

.PHONY	:	all	clean	fclean	re	bonus norm

# ${OBJ_DIR}/%.o	: %.c ${HEADER}
%.o	: %.c ${HEADER}
	${CC} ${CFLAGS} -c $< -o $@

${NAME}	:	${HEADER} ${OBJ}
	${CC} ${CFLAGS} ${SRCS} -o ${NAME}

# all		:	tmp ${NAME}
all		:	${NAME}

tmp		:
	mkdir -p ${OBJ_DIR}

clean	:
	${RM} ${OBJ}

fclean	:	clean
	${RM} ${NAME}

re		:	fclean	all

# bonus	:

norm	:
	norminette ${SRCS}
	norminette ${HEADER}