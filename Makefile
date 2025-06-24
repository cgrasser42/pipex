# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/23 23:37:46 by cgrasser          #+#    #+#              #
#    Updated: 2025/06/24 10:50:25 by cgrasser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BIN = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = build
	
SRC = here_doc.c main.c pipex.c utils.c

OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I $(LIBFT_PATH)/inc -I ./inc -c $< -o $@

all: $(BIN)

$(BIN): $(LIBFT) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(BIN)

$(LIBFT):
	make -s -C $(LIBFT_PATH)
	
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	make -s -C $(LIBFT_PATH) clean
	$(RM) $(OBJ_DIR)

fclean:
	make -s -C $(LIBFT_PATH) fclean
	$(RM) $(OBJ_DIR)
	$(RM) $(BIN)

re: fclean all

.PHONY: all clean fclean re