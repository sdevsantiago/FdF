# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/23 19:07:42 by sede-san          #+#    #+#              #
#    Updated: 2025/07/02 19:30:38 by sede-san         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ******************************* Output files ******************************* #

# Executable file name
NAME = fdf

# ************************** Compilation variables *************************** #

# Compiler
CC = cc

# Compilation flags
CFLAGS = -Wall -Wextra -Werror -Iinclude -pthread -Ofast

# Linker flags
LDFLAGS = -lm -ldl -lglfw

# Make command with no-print-directory flag
MAKE = make --no-print-directory

# ***************************** Style variables ****************************** #

# Define color codes
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m # No Color

# Emojis
EMOJI_BROOM = 🧹
EMOJI_CHECK = ✅
EMOJI_CROSS = ❌
EMOJI_WRENCH = 🔧
EMOJI_BOX = 📦

# ****************************** Source files ******************************** #

# Source files path
SRC_PATH = src

# Source files
SRC = \
	$(SRC_PATH)/fdf.c \

# ****************************** Object files ******************************** #

OBJ = $(SRC:.c=.o)

# Compile object files
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# ********************************* Rules ************************************ #

# Compile all
all: $(NAME)
.PHONY : all

$(NAME): lib $(OBJ)
	@echo "$(YELLOW)$(EMOJI_WRENCH) Compiling...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_BIN) $(LIBFT_BIN) $(GNL_BIN) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)$(EMOJI_CHECK) Compiled.$(RESET)"
.PHONY : $(NAME)

# Clean object files
clean:
	@echo "$(RED)$(EMOJI_BROOM) Cleaning object files...$(RESET)"
	@rm -f $(OBJ)
	@if [ -d $(LIBFT_PATH) ]; then \
		$(MAKE) -C $(LIBFT_PATH) clean; \
	fi
	@if [ -d $(GNL_PATH) ]; then \
		$(MAKE) -C $(GNL_PATH) clean; \
	fi
	@if [ -d $(MLX_PATH)/build ]; then \
		$(MAKE) -C $(MLX_PATH)/build clean; \
	fi
	@echo "$(GREEN)$(EMOJI_CHECK) Object files cleaned.$(RESET)"
.PHONY : clean

# Clean object files and library
fclean: clean
	@echo "$(RED)$(EMOJI_BOX) Cleaning binaries...$(RESET)"
	@rm -f $(NAME)
	@if [ -d $(LIBFT_PATH) ]; then \
		$(MAKE) -C $(LIBFT_PATH) fclean; \
	fi
	@if [ -d $(GNL_PATH) ]; then \
		$(MAKE) -C $(GNL_PATH) fclean; \
	fi
	@echo "$(GREEN)$(EMOJI_CHECK) Binaries cleaned.$(RESET)"
.PHONY : fclean

# Recompile
re: fclean all
.PHONY : re

# ********************************* Libraries ******************************** #

lib:
	@$(MAKE) libft
	@$(MAKE) get_next_line
	@$(MAKE) mlx
.PHONY : lib

LIB_PATH = lib

# ** MLX42 ** #

MLX = MLX42
MLX_REPO = https://github.com/codam-coding-college/MLX42.git
MLX_PATH = $(LIB_PATH)/$(MLX)
MLX_BIN = $(MLX_PATH)/build/libmlx42.a

mlx:
	@if [ ! -d $(MLX_PATH) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Cloning $(MLX)...$(RESET)"; \
		git clone $(MLX_REPO) $(MLX_PATH); \
		echo "$(GREEN)$(EMOJI_CHECK) $(MLX) cloned...$(RESET)"; \
	fi
	@if [ ! -f $(MLX_BIN) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Compiling $(MLX)...$(RESET)"; \
		cd $(MLX_PATH) && cmake -B build && cmake --build build -j4; \
		echo "$(GREEN)$(EMOJI_CHECK) $(MLX) compiled.$(RESET)"; \
	else \
		echo "$(GREEN)$(EMOJI_CHECK) $(MLX) already compiled.$(RESET)"; \
	fi
.PHONY : mlx

# ** Libft ** #

LIBFT = Libft
LIBFT_REPO = https://github.com/sdevsantiago/Libft.git
LIBFT_PATH = $(LIB_PATH)/$(LIBFT)
LIBFT_BIN = $(LIBFT_PATH)/libft.a

libft:
	@if [ ! -d $(LIBFT_PATH) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Cloning $(LIBFT)...$(RESET)"; \
		git clone $(LIBFT_REPO) $(LIBFT_PATH); \
		echo "$(GREEN)$(EMOJI_CHECK) $(LIBFT) cloned...$(RESET)"; \
	fi
	@if [ ! -f $(LIBFT_BIN) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Compiling $(LIBFT)...$(RESET)"; \
		$(MAKE) -C $(LIBFT_PATH) all bonus; \
		echo "$(GREEN)$(EMOJI_CHECK) $(LIBFT) compiled.$(RESET)"; \
	else \
		echo "$(GREEN)$(EMOJI_CHECK) $(LIBFT) already compiled.$(RESET)"; \
	fi
.PHONY : libft

# ** get_next_line ** #

GNL = get_next_line
GNL_REPO = https://github.com/sdevsantiago/get_next_line.git
GNL_PATH = $(LIB_PATH)/$(GNL)
GNL_BIN = $(GNL_PATH)/get_next_line.a

get_next_line:
	@if [ ! -d $(GNL_PATH) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Cloning $(GNL)...$(RESET)"; \
		git clone $(GNL_REPO) $(GNL_PATH); \
		echo "$(GREEN)$(EMOJI_CHECK) $(GNL) cloned...$(RESET)"; \
	fi
	@if [ ! -f $(GNL_BIN) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Compiling $(GNL)...$(RESET)"; \
		$(MAKE) -C $(GNL_PATH) all; \
		echo "$(GREEN)$(EMOJI_CHECK) $(GNL) compiled.$(RESET)"; \
	else \
		echo "$(GREEN)$(EMOJI_CHECK) $(GNL) already compiled.$(RESET)"; \
	fi
.PHONY : get_next_line
