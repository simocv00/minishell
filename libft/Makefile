# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 22:26:21 by makarkao          #+#    #+#              #
#    Updated: 2025/07/14 10:20:48 by makarkao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoll.c ft_calloc.c ft_chrinstr.c ft_concat.c ft_isalnum.c ft_isalpha.c \
	ft_isdigit.c ft_itoa.c ft_numericheck.c ft_putchar_fd.c ft_putnbr_fd.c \
	ft_putstr_fd.c ft_slashjoin.c ft_split.c ft_sthreecat.c ft_strchr.c \
	ft_strcmp.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	ft_strlen.c ft_strncmp.c ft_substr.c ft_strsjoin.c
		
OBJS = ${SRCS:.c=.o}
NAME = libft.a
LIBC = ar rcs
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}

clean:
	${RM} ${OBJS} ${BONUS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
