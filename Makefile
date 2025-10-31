# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/29 10:14:26 by pioncha2          #+#    #+#              #
#    Updated: 2025/10/31 20:19:22 by pioncha2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Configuration ---
NAME = minishell

# --- Directories ---
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

LIBFT_DIR = lib/libft

# --- Libraries ---
LIBFT = $(LIBFT_DIR)/libft.a

# --- Compiler and Flags ---
CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS = 
INCLUDES = -I $(INC_DIR) -I $(LIBFT_DIR) 
LIBS = -L $(LIBFT_DIR) -lft -lreadline #-lhistory

# --- Source Files ---
SRC_FILES = main.c \
			utils_tab.c \
			utils_check.c \
			utils_env.c \
			reader.c \
			tokenizer.c \
			debug.c \
			exec_cmd.c \
			exec_builtin.c \
			exec_redirect.c \
			builtin_cmds1.c \
			builtin_cmds2.c \
			cmds.c \
			pipes.c \
			pipes_utils.c \
			end.c \
			parser_cmd.c \
			parser_fd.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# --- Colors ---
RESET = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m

# --- Main Rules ---
all: $(NAME)

$(LIBFT):
	make --silent -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

# --- Compilation Rule ---
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minishell.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# --- Cleaning ---
clean:
	rm -rf $(OBJ_DIR)
	@make --silent -C $(LIBFT_DIR) clean
	@echo "$(RED)Object files cleaned!$(RESET)"

fclean: clean
	rm -f $(NAME)
	@make --silent -C $(LIBFT_DIR) fclean
	@echo "$(RED)Binaries and libraries cleaned!$(RESET)"

re: fclean all

# --- Phony Targets ---
.PHONY: all clean fclean re 