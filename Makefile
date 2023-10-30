# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/14 15:00:13 by afarheen          #+#    #+#              #
#    Updated: 2023/08/18 14:01:51 by afarheen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADER = ./include

CC = cc -g3 

CFLAGS = -Wall -Wextra -Werror -g -I $(HEADER)
# -Werror
SRCS = main.c utils.c builtins.c list_fns.c export.c env.c free.c pipes.c path.c \
		dollar_exp.c dollar_utils.c quotations.c spacings.c redirections.c \
		builtins2.c builtins3.c utils2.c redirections2.c pipes2.c pipes3.c parsing_help.c \
		synt_error.c utils_3.c

OBJS = $(SRCS:.c=.o)


$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(OBJS) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include -L libft -l ft -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -rf $(NAME)
	rm -rf minishell.dSYM

re: fclean all