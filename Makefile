# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etregoni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/21 14:58:27 by etregoni          #+#    #+#              #
#    Updated: 2017/10/07 19:13:28 by etregoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# SV - Server specific files
# CL - Client specific files
# HL - Files containing helper functions used in both client and server
# CM - Files with commands to be executed by server


NAME_CL = client
NAME_SV = server
CFLAGS = -Wall -Werror -Wextra -g
MDIR = $(shell pkg-config --variable=MDIR pocketsphinx)
SPHX_FLAGS = $(shell pkg-config --cflags pocketsphinx sphinxbase)
SPHX_LIBS = $(shell pkg-config --libs pocketsphinx sphinxbase)
SDL_LIBS = $(shell sdl2-config --cflags --libs)

SRC_SV = server.c init_conn.c
SRC_CL = client.c commands.c more_commands.c even_more_commands.c \
			smalltalk.c recog.c
SRC_HL = network_helpers.c
SRC_CM = api_calls.c web_search.c json_parser.c  server_startup_concept.c extra.c


OBJ_CL_FILES = $(SRC_CL:.c=.o)
OBJ_SV_FILES = $(SRC_SV:.c=.o)
OBJ_HL_FILES = $(SRC_HL:.c=.o)
OBJ_CM_FILES = $(SRC_CM:.c=.o)

HL_DIR = ./src/helpers/
CL_DIR = ./src/client/
SV_DIR = ./src/server/
CM_DIR = ./src/client/cmds/
OBJ_DIR = ./obj/
OBJ_CL_DIR = ./obj/client/
OBJ_CM_DIR = ./obj/client/
OBJ_SV_DIR = ./obj/server/
OBJ_HL_DIR = ./obj/helpers/
INC_DIR = ./include/
LIBFT_DIR = ./libft/
SDL = ./SDL/include/
SPHX_DIR = ./cmusphinx/
JSMN_DIR = ./jsmn/

OBJ_CL = $(addprefix $(OBJ_CL_DIR), $(OBJ_CL_FILES))
OBJ_SV = $(addprefix $(OBJ_SV_DIR), $(OBJ_SV_FILES))
OBJ_HL = $(addprefix $(OBJ_HL_DIR), $(OBJ_HL_FILES))
OBJ_CM = $(addprefix $(OBJ_CM_DIR), $(OBJ_CM_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
JSMN = $(addprefix $(JSMN_DIR), libjsmn.a)

LINK = -L $(LIBFT_DIR) -L $(JSMN_DIR) -lft -lcurl -ljsmn $(SPHX_LIBS) $(SDL_LIBS)

all: obj $(LIBFT) $(JSMN) $(NAME_CL) $(NAME_SV)

obj:
	@mkdir -p $(OBJ_CM_DIR)
	@mkdir -p $(OBJ_CL_DIR)
	@mkdir -p $(OBJ_SV_DIR)
	@mkdir -p $(OBJ_HL_DIR)

$(OBJ_CL_DIR)%.o:$(CL_DIR)%.c
	@gcc -I $(LIBFT_DIR) -I $(INC_DIR) -I $(SDL) -I $(JSMN_DIR) -DMDIR=\"$(MDIR)\" $(SPHX_FLAGS) -o $@ -c $<

$(OBJ_SV_DIR)%.o:$(SV_DIR)%.c
	@gcc -I $(LIBFT_DIR) -I $(INC_DIR) -I $(SDL) -I $(JSMN_DIR) -DMDIR=\"$(MDIR)\" $(SPHX_FLAGS) -o $@ -c $<

$(OBJ_HL_DIR)%.o:$(HL_DIR)%.c
	@gcc -I $(LIBFT_DIR) -I $(INC_DIR) -I $(SDL) -I $(JSMN_DIR) -DMDIR=\"$(MDIR)\" $(SPHX_FLAGS) -o $@ -c $<

$(OBJ_CM_DIR)%.o:$(CM_DIR)%.c
	@gcc -I $(LIBFT_DIR) -I $(INC_DIR) -I $(SDL) -I $(JSMN_DIR) -DMDIR=\"$(MDIR)\" $(SPHX_FLAGS) -o $@ -c $<

$(JSMN):
	@echo "\033[32mCompiling JSMN...\033[0m"
	@make -C $(JSMN_DIR)
	@echo "\033[1;4;32m[\xE2\x9C\x94] libjsmn created.\033[0m\n"

$(LIBFT):
	@echo "\033[32mCompiling libft...\033[0m"
	@make -C $(LIBFT_DIR)
	@echo "\033[1;4;32m[\xE2\x9C\x94] libft created.\033[0m\n"

$(NAME_CL): $(OBJ_CL) $(OBJ_HL) $(OBJ_CM)
	@echo "\033[32mCompiling $(NAME_CL)...\033[0m"
	@gcc $(OBJ_HL) $(OBJ_CL) $(OBJ_CM) $(LINK) $(SDL_LIBS) -lm -o $(NAME_CL)
	@echo "\033[1;4;32m[\xE2\x9C\x94] $(NAME_CL) Created.\033[0m\n"

$(NAME_SV): $(OBJ_SV) $(OBJ_HL)
	@echo "\033[32mCompiling $(NAME_SV)...\033[0m"
	@gcc $(OBJ_SV) $(OBJ_HL) $(LINK) $(SPHX_LIBS) -lm -o $(NAME_SV)
	@echo "\033[1;4;32m[\xE2\x9C\x94] $(NAME_SV) Created.\033[0m\n"

clean:
	@echo "\033[31mRemoving source objects...\033[0m"
	@rm -rf $(OBJ_DIR)
	@echo "\033[4;31m[\xE2\x9D\x8C ] Source objects removed!\033[0m\n"
	@echo "\033[31mRemoving libft objects...\033[0m"
	@make -C $(LIBFT_DIR) clean
	@echo "\033[4;31m[\xE2\x9D\x8C ] libft Objects removed!\033[0m\n"
	@echo "\033[1;4;91m-----All objects removed!-----\033[0m\n"

clean_client:
	@echo "\033[31mRemoving client objects...\033[0m"
	@rm -rf $(OBJ_CL_DIR)
	@rm -rf $(OBJ_HL_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "\033[4;31m[\xE2\x9D\x8C ] Client objects removed!\033[0m"

clean_server:
	@echo "\033[31mRemoving server objects...\033[0m"
	@rm -rf $(OBJ_SV_DIR)
	@rm -rf $(OBJ_HL_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "\033[4;31m[\xE2\x9D\x8C ] Server objects removed!\033[0m"

fclean: clean
	@echo "\033[31mRemoving $(NAME_CL)...\033[0m"
	@rm -f $(NAME_CL)
	@echo "\033[4;31m[\xE2\x9D\x8C ] $(NAME_CL) removed!\033[0m\n"
	@echo "\033[31mRemoving $(NAME_SV)...\033[0m"
	@rm -f $(NAME_SV)
	@echo "\033[4;31m[\xE2\x9D\x8C ] $(NAME_SV) removed!\033[0m\n"
	@echo "\033[31mRemoving libft objects and libft.a...\033[0m"
	@make -C $(LIBFT_DIR) fclean
	@echo "\033[4;31m[\xE2\x9D\x8C ] libft objects and libft.a removed!!\033[0m\n"
	@echo "\033[1;4;31m-----All objects, executables and lib files removed!-----\033[0m\n"

re: fclean all

.PHONY: clean clean_client clean_server fclean all re
