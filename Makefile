# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 11:51:36 by snemoto           #+#    #+#              #
#    Updated: 2023/05/04 15:53:51 by snemoto          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINISHELL_SRCS = \
					main.c \
					destructor.c \
					error.c \
					step3.exec_path.c \
					step4.exec_filename.c \
					step5-0.bool.c \
					step5-1.tokenize.c \
					step5-2.token_to_argv.c \
					step5-3.expand.c \
					step5-4.expand_op.c \
					step7.parse.c \
					step9-0.redirect.c \
					step9-1.redirect_op.c \
					step10.pipe.c

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
