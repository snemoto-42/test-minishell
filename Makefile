# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 11:51:36 by snemoto           #+#    #+#              #
#    Updated: 2023/05/04 19:43:12 by snemoto          ###   ########.fr        #
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
					tokenize_is_op.c \
					tokenize_is.c \
					tokenize_to_argv.c \
					tokenize_word.c \
					tokenize.c

NAME	= minishell
CC		= cc
RLDIR	= $(shell brew --prefix readline)
INCLUDE	= -I include -I$(RLDIR)/include
CFLAGS	= -Wall -Wextra -Werror $(INCLUDE)
# CFLAGS	= -Wall -Wextra -Werror -fsanitize=address
LIBS	= -lreadline -L$(RLDIR)/lib
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