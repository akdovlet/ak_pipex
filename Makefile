# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 13:57:12 by akdovlet          #+#    #+#              #
#    Updated: 2024/04/29 18:17:13 by akdovlet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
LIBDIR	=	lib
LIBFT	= 	$(LIBDIR)/libft/libft.a

SRC		:=	main.c		\
			test.c		\
			parsing.c	\
			px_split.c
SRC_DIR:=	src
BUILD	:=	.build
SRC 	:=	$(addprefix $(SRC_DIR)/, $(SRC))
OBJS 	:=	$(patsubst $(SRC_DIR)/%.c, $(BUILD)/%.o, $(SRC))
DEPS 	:=	$(OBJS:.o=.d)

CC		:=	cc
CFLAGS	:=	-MMD -MP -Iinclude -I$(LIBDIR)/libft/include -g3

all: create_dirs $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(BUILD)/%.o: $(SRC_DIR)/%.c
	@printf "\033[0;32%sm\tCompiling: $<\033[0m\n";
	@$(CC) $(CFLAGS) -c $< -o $@

create_dirs:
	@if [ ! -d "$(BUILD)" ]; then mkdir $(BUILD); fi

$(LIBFT):
	@$(MAKE) -C $(LIBDIR)/libft

clean:
	@if [ -d "$(BUILD)" ]; then $(RM) -r $(BUILD) && echo "\033[1;31m$(NAME) .o files have been deleted\033[0m"; fi
	@$(MAKE) --no-print-directory clean -C $(LIBDIR)/libft

fclean: clean
	@if [ -f "$(NAME)" ]; then $(RM) $(NAME) && echo "\033[1;31m$(NAME) executable has been deleted\033[0m"; fi
	@$(MAKE) --no-print-directory fclean -C $(LIBDIR)/libft

re: fclean all

-include $(DEPS)

.PHONY: all create_dirs clean fclean re
