# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 09:37:01 by afarheen          #+#    #+#              #
#    Updated: 2023/08/15 19:52:37 by afarheen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

MY_SOURCES = ft_bzero.c ft_split.c ft_strcmp.c ft_strdup.c ft_isalnum.c\
			ft_strlen.c ft_strstr.c ft_atoi.c ft_calloc.c ft_strchr.c\
			ft_strjoin.c ft_strncpy.c ft_printf.c ft_putnbr_base.c \
			ft_strncmp.c get_next_line.c refined_split.c ft_itoa.c ft_isspace.c

MY_OBJS = $(MY_SOURCES:.c=.o)
CFLAGS += -Wall -Werror -Wextra
CC = cc

all: $(NAME)
$(NAME): $(MY_OBJS)
	$(CC) $(CFLAGS) -c $(MY_SOURCES)
	ar -rcs $(NAME) $(MY_OBJS)
clean:
	rm -f $(MY_OBJS)
fclean:  clean
	rm -f $(NAME)
re: fclean all
