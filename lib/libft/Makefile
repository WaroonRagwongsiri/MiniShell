# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/29 10:14:26 by pioncha2          #+#    #+#              #
#    Updated: 2025/10/29 10:27:00 by pioncha2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Configuration ---
NAME = libft.a

# --- Directories ---
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj


# --- Compiler and Flags ---
CC = cc
CFLAGS = -Wall -Wextra -Werror 
INCLUDES = -I $(INC_DIR) 

# --- Source Files ---
SRC_FILES = 	ft_tolower.c ft_toupper.c ft_isprint.c ft_isascii.c ft_isalnum.c ft_isdigit.c \
				ft_isalpha.c ft_atoi.c ft_strlen.c ft_strlcat.c ft_strncmp.c ft_strdup.c ft_calloc.c \
				ft_memcpy.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_bzero.c ft_memchr.c ft_memcmp.c \
				ft_memset.c ft_memmove.c ft_strlcpy.c ft_itoa.c ft_strjoin.c ft_split.c ft_striteri.c \
				ft_strmapi.c ft_substr.c ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
				ft_putnbr_fd.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
				ft_lstsize_bonus.c ft_lstlast_bonus.c ft_atoi_base.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# --- Colors ---
RESET = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m

# --- Main Rules ---
all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJS)
	ar crs $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

# --- Compilation Rule ---
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/libft.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# --- Cleaning ---
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# --- Phony Targets ---
.PHONY: all clean fclean re 