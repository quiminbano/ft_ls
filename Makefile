# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 12:46:54 by corellan          #+#    #+#              #
#    Updated: 2024/04/25 16:54:28 by corellan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = ft_ls.c ft_ls_flags.c ft_ls_fill_lst.c ft_ls_lst_utils.c \
ft_ls_sort_lst.c ft_ls_permissions.c ft_ls_print.c ft_ls_paddings.c \
ft_ls_dir.c ft_ls_dir_loop.c

OBJ = $(SRC:.c=.o)

LIBFT = -Llibft -lft

CC = cc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
		$(MAKE) bonus -C ./libft
		$(CC) $(FLAGS) -I. $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c
		$(CC) $(FLAGS) -I. -c $< -o $@

clean:
		$(MAKE) clean -C ./libft
		rm -f $(OBJ)

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean
		
