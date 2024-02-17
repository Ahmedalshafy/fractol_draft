# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/17 07:47:16 by aalshafy          #+#    #+#              #
#    Updated: 2024/02/17 07:47:22 by aalshafy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, main.c events.c init.c math.c ft_printf.c render.c helper.c printf_helper.c)
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L minilibx -lmlx -framework OpenGL -framework AppKit
MINILIBX_DIR = minilibx
CC = cc

all: minilibx $(NAME) clean
minilibx:
	@echo "Building minilibx..."
	@make -C $(MINILIBX_DIR)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)


fclean: clean
	rm -f $(NAME)
	make -C $(MINILIBX_DIR) clean

re: fclean all

.PHONY: all clean fclean re minilibx