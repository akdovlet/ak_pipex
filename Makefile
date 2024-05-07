# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 13:57:12 by akdovlet          #+#    #+#              #
#    Updated: 2024/05/07 00:44:24 by akdovlet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
LIBDIR	=	lib
LIBFT	= 	$(LIBDIR)/libft/libft.a

SRC		:=	check_file.c	\
			free.c			\
			main.c			\
			mario_gaming.c	\
			parsing.c		\
			px_split.c		\
			seek_and_execute.c	\
			setup.c
SRC_DIR	:=	src
BUILD	:=	.build
SRC 	:=	$(addprefix $(SRC_DIR)/, $(SRC))
OBJ 	:=	$(patsubst $(SRC_DIR)/%.c, $(BUILD)/%.o, $(SRC))
DEPS 	:=	$(OBJ:.o=.d)

CC		:=	cc
CFLAGS	:=	-MMD -MP -Iinclude -I$(LIBDIR)/libft/include -g3

all: create_dirs $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(BUILD)/%.o: $(SRC_DIR)/%.c
	@printf "\033[1;32%sm\tCompiled: $<\033[0m\n";
	@$(CC) $(CFLAGS) -c $< -o $@

create_dirs:
	@if [ ! -d "$(BUILD)" ]; then mkdir $(BUILD); fi

$(LIBFT):
	@$(MAKE) -C $(LIBDIR)/libft

clean:
	@if [ -d "$(BUILD)" ]; then $(RM) -rf $(BUILD) && echo "\033[1;31m\tDeleted: $(NAME) $(BUILD)\033[0m"; fi
	@$(MAKE) --no-print-directory clean -C $(LIBDIR)/libft

fclean: clean
	@if [ -f "$(NAME)" ]; then $(RM) -rf $(NAME) && echo "\033[1;31m\tDeleted: $(NAME)\033[0m"; fi
	@$(MAKE) --no-print-directory fclean -C $(LIBDIR)/libft

re: fclean all

-include $(DEPS)

.PHONY: all create_dirs clean fclean re
