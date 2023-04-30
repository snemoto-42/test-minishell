# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 11:51:36 by snemoto           #+#    #+#              #
#    Updated: 2023/04/30 13:34:43 by snemoto          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINISHELL_SRCS = \
					main.c \
					step3.exec_path.c \
					step4.exec_filename.c

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
# CFLAGS	= -Wall -Wextra -Werror -fsanitize=address
RM		= rm -f
NAME	= minishell
SRCS	= ${MINISHELL_SRCS}
OBJS	= ${MINISHELL_SRCS:.c=.o}

$(NAME): ${OBJS}
		${CC} ${CFLAGS} ${SRCS} -lreadline -o ${NAME}

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

bonus:	all

.PHONY: all clean fclean re bonus
