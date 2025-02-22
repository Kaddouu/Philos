# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 21:49:00 by ilkaddou          #+#    #+#              #
#    Updated: 2025/02/22 19:06:04 by ilkaddou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

OBJ_DIR = obj

SRCS = main.c utils.c monitor.c init.c simulation.c philo_routine.c parsing.c

OBJ = $(OBJ_DIR)/main.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/monitor.o \
      $(OBJ_DIR)/init.o $(OBJ_DIR)/simulation.o $(OBJ_DIR)/philo_routine.o \
      $(OBJ_DIR)/parsing.o

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re