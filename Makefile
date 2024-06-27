# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 12:46:54 by corellan          #+#    #+#              #
#    Updated: 2024/06/27 13:49:31 by corellan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = $(addprefix mandatory_src/, ft_ls.c ft_ls_flags.c ft_ls_fill_lst.c \
ft_ls_lst_utils.c ft_ls_sort_lst.c ft_ls_permissions.c ft_ls_print.c \
ft_ls_paddings.c ft_ls_dir.c ft_ls_dir_loop.c ft_ls_special_files.c \
ft_ls_symlink.c)

SRC_B = $(addprefix bonus_src/, ft_ls_bonus.c ft_ls_flags_bonus.c \
ft_ls_fill_lst_bonus.c ft_ls_lst_utils_bonus.c ft_ls_sort_lst_bonus.c \
ft_ls_permissions_bonus.c ft_ls_print_bonus.c ft_ls_paddings_bonus.c \
ft_ls_dir_bonus.c ft_ls_dir_loop_bonus.c ft_ls_special_files_bonus.c \
ft_ls_symlink_bonus.c ft_ls_ext_bonus.c ft_ls_column_format_bonus.c \
ft_ls_colors_bonus.c ft_ls_column_pad_print_bonus.c ft_ls_lst_del_bonus.c)

OBJ = $(SRC:.c=.o)

OBJ_B = $(SRC_B:.c=.o)

LIBFT = -Llibft -lft

CC = cc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
		$(MAKE) bonus -C ./libft
		$(CC) $(FLAGS) -Iincludes $(OBJ) $(LIBFT) -o $(NAME)

bonus: .bonus

.bonus: $(OBJ_B)
		$(MAKE) bonus -C ./libft
		$(CC) $(FLAGS) -Iincludes $(OBJ_B) $(LIBFT) -o $(NAME)
		@touch .bonus

mandatory_src/%.o: mandatory_src/%.c
		$(CC) $(FLAGS) -Iincludes -c $< -o $@

bonus_src/%.o: bonus_src/%.c
		$(CC) $(FLAGS) -Iincludes -c $< -o $@

clean:
		$(MAKE) clean -C ./libft
		rm -f $(OBJ) $(OBJ_B)
		@rm -f .bonus

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean
		
