# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 13:57:12 by akdovlet          #+#    #+#              #
#    Updated: 2024/04/25 19:51:04 by akdovlet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
LIBDIR	=	library
LIBFT	= 	$(LIBDIR)/libft/libft.a

SRCS	:=	main.c		\
			test.c		\
			parsing.c	\
			px_split.c
SRCS 	:=	$(addprefix source/, $(SRCS))
OBJS 	:=	$(patsubst source/%.c, .object/%.o, $(SRCS))
DEPS 	:=	$(OBJS:.o=.d)

CC		:=	cc
CFLAGS	:=	-MMD -MP -Iinclude -I$(LIBDIR)/libft/include -g3

all: create_dirs $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

.object/%.o: source/%.c
	@printf "\033[0;32%sm\tCompiling: $<\033[0m\n";
	@$(CC) $(CFLAGS) -c $< -o $@

create_dirs:
	@if [ ! -d ".object" ]; then mkdir .object; fi

$(LIBFT):
	@$(MAKE) -C $(LIBDIR)/libft

clean:
	@if [ -d ".object" ]; then rm -rf .object && echo "\033[1;31mpipex .o files have been deleted\033[0m"; fi
	@$(MAKE) --no-print-directory clean -C $(LIBDIR)/libft

fclean: clean
	@if [ -f "pipex" ]; then rm -rf pipex && echo "\033[1;31mpipex executable has been deleted\033[0m"; fi
	@$(MAKE) --no-print-directory fclean -C $(LIBDIR)/libft

re: fclean all

-include $(DEPS)

.PHONY: all create_dirs clean fclean re
