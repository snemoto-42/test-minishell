# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 11:51:36 by snemoto           #+#    #+#              #
#    Updated: 2023/05/04 20:39:53 by snemoto          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINISHELL_SRCS = \
					destructor.c \
					error_location.c \
					error_msg.c \
					exec.c \
					expand_append.c \
					expand_is.c \
					expand_remove.c \
					expand_var.c \
					main.c \
					parse_append.c \
					parse.c \
					pipe.c \
					redirect_op.c \
					redirect_util.c \
					redirect.c \
					signal_util.c \
					signal.c \
					tokenize_is.c \
					tokenize_to_argv.c \
					tokenize_word.c \
					tokenize.c

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror $(INCLUDE)
LIBS	= -lreadline
RM		= rm -f
SRCS	= ${MINISHELL_SRCS}
OBJS	= ${MINISHELL_SRCS:.c=.o}

all:	$(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(LIBS) -o $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

bonus:	all

.PHONY: all clean fclean re bonus

OS := $(shell uname -s)

ifeq ($(OS),Linux)

endif

ifeq ($(OS),Darwin)
		RLDIR 	= $(shell brew --prefix readline)
		INCLUDE += -I$(RLDIR)/include
		LIBS	+= -L$(RLDIR)/lib
endif