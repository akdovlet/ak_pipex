# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 13:57:12 by akdovlet          #+#    #+#              #
#    Updated: 2024/04/23 18:31:10 by akdovlet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT	= 	library/libft/libft.a
PRINTF	=	library/printf/libftprintf.a

SRCS :=		main.c	\
			test.c	\
			parsing.c
SRCS := 	$(addprefix source/, $(SRCS))
OBJS := 	$(patsubst source/%.c, object/%.o, $(SRCS))
DEPS := 	$(OBJS:.o=.d)

CC := cc
CFLAGS := -MMD -MP -Iinclude -Ilibrary/libft/include -Ilibrary/printf/include

all: create_dirs $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $(OBJS) $(PRINTF) $(LIBFT) -lXext -lX11 -lm -lz -o $(NAME)

object/%.o: source/%.c
	@printf "\033[0;32%sm\tCompiling: $<\033[0m\n";
	@$(CC) $(CFLAGS) -c $< -o $@

# run: $(NAME)
# 	@./fdf maps/test_maps/t1.fdf

create_dirs:
	@if [ ! -d "object" ]; then mkdir object; fi

$(LIBFT):
	@$(MAKE) -C library/libft

$(PRINTF):
	@$(MAKE) -C library/printf

# run: $(NAME)
# 	./fdf $(runargs)

clean:
	@if [ -d "object" ]; then rm -rf object && echo "\033[1;31mFdf .o files have been deleted\033[0m"; fi
	@$(MAKE) --no-print-directory clean -C library/libft
	@$(MAKE) --no-print-directory clean -C library/printf

fclean: clean
	@if [ -f "pipex" ]; then rm -rf pipex && echo "\033[1;31mpipex executable has been deleted\033[0m"; fi
	@$(MAKE) --no-print-directory fclean -C library/libft
	@$(MAKE) --no-print-directory fclean -C library/printf

re: fclean all

-include $(DEPS)

.PHONY: all create_dirs clean fclean re
