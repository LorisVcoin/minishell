# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namichel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/04 00:09:15 by namichel          #+#    #+#              #
#    Updated: 2025/05/29 21:14:37 by lviravon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell

CC		:= gcc

SRCFILES	:= main.c \
					free_utils.c \
					echo.c \
					env.c \
					unset.c \
					export.c \
					cd.c \
					heredoc.c \
					pwd.c \
					export_the_void.c \
					exec.c \
					duplicate_env.c \
					token_split.c \
					set_cmd.c \
					parsing.c	\
					parse_cut_space.c \
					parse_env.c \
					parse_exitval.c \
					parse_space.c \
					exit.c \
					parse_quote.c
OBJS := $(SRCFILES:.c=.o)
CFLAGS := -Wall -Wextra -Werror -g -I -includes

LDFLAGS := -lreadline -lft -Llibft

LIBFT := ./libft/libft.a

all: $(NAME) $(LIBFT)

$(LIBFT):
	$(MAKE) bonus -C ./libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./libft
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
