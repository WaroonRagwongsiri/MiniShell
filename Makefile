# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/29 10:14:26 by pioncha2          #+#    #+#              #
#    Updated: 2025/11/04 20:35:57 by pioncha2         ###   ########.fr        #
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
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -I $(INC_DIR) -I $(LIBFT_DIR) 
LIBS = -L $(LIBFT_DIR) -lft -lreadline -lhistory

# For MacOS
ifeq ($(shell uname),Darwin)
	READLINE_PATH = $(shell brew --prefix readline)
	INCLUDES += -I $(READLINE_PATH)/include
	LIBS += -L $(READLINE_PATH)/lib 
endif

# define hostname
HOST = $(shell hostname -s)
INCLUDES += -D HOSTNAME=\"$(HOST)\"

# --- Source Files ---
SRC_FILES = main.c \
			utils_tab.c \
			utils_check.c \
			utils_env.c \
			utils_quotes.c \
			reader.c \
			reader_quotes.c \
			tokenizer.c \
			debug.c \
			exec_cmd.c \
			exec_builtin.c \
			builtin_cmds1.c \
			builtin_cmds2.c \
			builtin_utils.c \
			cmds.c \
			pipes.c \
			pipes_utils.c \
			end.c \
			parser_cmd.c \
			parser_get_info.c \
			parser_check.c \
			parser_in_files.c \
			parser_out_files.c \
			heredoc.c \
			iofiles.c \
			iofiles2.c \
			iofiles_utils.c \
			expander.c \
			signal.c \
			signal2.c \
			utils_cmd_path.c \
			waiter.c \
			builtin_cmds3.c \
			builtin_cmds4.c \
			builtin_utils2.c \
			builtin_export_utils.c

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