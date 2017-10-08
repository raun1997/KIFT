# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scollet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/06 18:32:14 by scollet           #+#    #+#              #
#    Updated: 2017/10/06 18:32:15 by scollet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# this is literally ripped from my fdf, i just gotta rewrite it

NAME = $(client/server)
PATH_SRC = ./
FT = 	../pocketsphinx/include \
			../sphinxbase/include/ \
			../sphinxbase/include/sphinxbase
MLX = ./minilibx_macos/mlx.h

SRC = draw.c \
			error.c \
			grid.c \
			key.c \
			main.c \
			tools.c

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra

HEAD = fdf.h

OBJ = $(patsubst %.c,%.o,$(addprefix $(PATH_SRC), $(SRC)))

#LIB = -L libft -lft -L minilibx_macos -lmlx
#CFLAGS += -Wall -Wextra -I libft -I minilibx_macos

server:

client:

all: $(NAME)
	@echo "\033[04;32mCompilation completed!\033[0m"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -I $(FT)
	@$(CC) -o $(NAME) $(OBJ) -L libft/ -lft -L minilibx_macos/ -lmlx -framework OpenGL -framework AppKit

.PHONY: clean fclean re
		#@make -C minilibx_macos
		#@gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) #-framework OpenGL -framework AppKit
	#$(OBJ):
		#@gcc $(CFLAGS) -I includes -I libft/includes -c $*.c -o $@

clean:
	@make -C libft clean
	@make -C minilibx_macos clean
	@echo "Cleaning .o processing ..."
	@rm -rf $(OBJ)
	@echo "Cleaning .o completed !"

fclean: clean
	@make -C libft clean
	@make -C minilibx_macos clean
	@echo "Fclean processing ..."
	@rm -f $(NAME)
	@echo "Fclean completed !"

re: fclean all
