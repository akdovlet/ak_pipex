# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 13:57:12 by akdovlet          #+#    #+#              #
#    Updated: 2024/05/22 16:51:32 by akdovlet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	pipex
BNAME	:=	pipex_bonus
LIBDIR	:=	lib
LIBFT	:= 	$(LIBDIR)/libft/libft.a

SRC		:=	ak_pipe.c			\
			ak_pipeout.c		\
			clear_exit.c		\
			cmd_exe.c			\
			dr_here.c			\
			env_access.c		\
			main.c				\
			open_infile.c		\
			open_outfile.c		\
			px_split.c			\
			seek_and_execute.c	\
			setup.c

BSRC	:=	ak_pipe.c			\
			ak_pipeout.c		\
			clear_exit.c		\
			cmd_exe.c			\
			dr_here.c			\
			env_access.c		\
			main_bonus.c		\
			open_infile.c		\
			open_outfile.c		\
			px_split.c			\
			seek_and_execute.c	\
			setup.c
SRC_DIR	:=	src
BUILD	:=	.build
SRC 	:=	$(addprefix $(SRC_DIR)/, $(SRC))
BSRC 	:=	$(addprefix $(SRC_DIR)/, $(BSRC))
OBJ 	:=	$(patsubst $(SRC_DIR)/%.c, $(BUILD)/%.o, $(SRC))
BOBJ 	:=	$(patsubst $(SRC_DIR)/%.c, $(BUILD)/%.o, $(BSRC))
DEPS 	:=	$(OBJ:.o=.d)
BDEPS	:=	$(BOBJ:.o=.d)

CC		:=	cc
CFLAGS	:=	-Wall -Werror -Wextra -MMD -MP -Iinclude -I$(LIBDIR)/libft/include -g

all: create_dirs $(NAME)

bonus:	create_dirs $(BNAME)

both: all bonus

create_dirs: $(BUILD)

$(BUILD):
	@if [ ! -d $(BUILD) ]; then mkdir $(BUILD); fi

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(BNAME): $(BOBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(BOBJ) $(LIBFT) -o $(BNAME)

$(BUILD)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[1;32%sm\tCompiled: $<\033[0m\n";

$(LIBFT):
	@$(MAKE) --no-print-directory -C  $(LIBDIR)/libft

clean:
	@if [ -d $(BUILD) ]; then $(RM) -rf $(BUILD) && echo "\033[1;31m\tDeleted: $(NAME) $(BUILD)\033[0m"; fi
	@$(MAKE) --no-print-directory clean -C $(LIBDIR)/libft

fclean: clean
	@if [ -f $(NAME) ]; then $(RM) -rf $(NAME) && echo "\033[1;31m\tDeleted: $(NAME)\033[0m"; fi
	@if [ -f $(BNAME) ]; then $(RM) -rf $(BNAME) && echo "\033[1;31m\tDeleted: $(BNAME)\033[0m"; fi
	@$(MAKE) --no-print-directory fclean -C $(LIBDIR)/libft

re: fclean all

-include $(DEPS)
-include $(BDEPS)

.PHONY: all create_dirs clean fclean re bonus both
