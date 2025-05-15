# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namichel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/13 22:00:56 by namichel          #+#    #+#              #
#    Updated: 2025/03/05 03:23:35 by namichel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		:=	ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
					ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
					ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
					ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c ft_memcpy.c \
					ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
					ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
					ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_striteri.c  \
					pf_hexa.c \
					pf_memcpy.c \
					pf_putstr.c \
					pf_substr.c \
					pf_hexa_p.c \
					pf_putchar.c \
					pf_strchr.c \
					ft_printf.c \
					pf_itoa.c \
					pf_putchar_fd.c \
					pf_strdup.c \
					pf_itoa_u.c \
					pf_putpercent.c \
					pf_strlen.c \

OBJS		:=	$(SRCS:.c=.o)

BONUS		:=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
					ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
					ft_lstmap.c ft_lstnew.c ft_lstsize.c

BONUS_OBJS	:= $(BONUS:.c=.o)

CC			:= gcc
RM			:= rm -f
CFLAGS		:= -Wall -Wextra -Werror

NAME		:= libft.a

all:	$(NAME)

$(NAME):	$(OBJS)
				ar rcs $(NAME) $(OBJS)
				ranlib $(NAME)

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:		clean
				$(RM) $(NAME)

re:			fclean $(NAME)

bonus:		$(OBJS) $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
				ranlib $(NAME)

.PHONY:		all clean fclean re bonus
