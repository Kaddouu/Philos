# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 21:49:00 by ilkaddou          #+#    #+#              #
#    Updated: 2025/02/22 14:22:12 by ilkaddou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = philo

# Chemins des répertoires
OBJ_DIR = obj

# Fichiers sources du projet principal
SRCS = main.c utils.c monitor.c init.c simulation.c philo_routine.c parsing.c
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Options de compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread

# Règle principale
all: $(OBJ_DIR) $(NAME)

# Création du dossier obj
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation de l'exécutable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Nettoyage des fichiers objets
clean:
	rm -rf $(OBJ_DIR)

# Nettoyage complet
fclean: clean
	rm -f $(NAME)

# Récompilation complète
re: fclean all

.PHONY: all clean fclean re
