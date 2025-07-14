# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/23 19:07:42 by sede-san          #+#    #+#              #
#    Updated: 2025/07/13 17:53:02 by sede-san         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ******************************* Output files ******************************* #

# Executable file name
NAME = fdf

# ************************** Compilation variables *************************** #

# Compiler
CC = cc

# Compilation flags
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast

HEADERS = -I $(FDF_INCLUDE_PATH) -I $(MLX_INCLUDE_PATH) -I $(GNL_INCLUDE_PATH) -I $(LIBFT_INCLUDE_PATH)

DFLAGS = -g3

ifeq ($(DEBUG), 1)
	CFLAGS += $(DFLAGS)
endif

# Make command with no-print-directory flag
MAKE += --no-print-directory

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
	$(SRC_PATH)/check_row.c \
	$(SRC_PATH)/save_row.c \
	$(SRC_PATH)/setup_mlx.c \
	$(SRC_PATH)/hooks/check_keypress.c \
	$(SRC_PATH)/hooks/show_fps.c \
	$(SRC_PATH)/hooks/update_window_size.c \
	$(SRC_PATH)/utils/free_map.c \
	$(SRC_PATH)/utils/handle_error.c

FDF_INCLUDE_PATH = ./include

# ****************************** Object files ******************************** #

OBJS = $(SRC:.c=.o)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

# ********************************* Rules ************************************ #

# Compile all
all: lib $(NAME)
.PHONY : all

$(NAME): $(OBJS)
	@echo "$(YELLOW)$(EMOJI_BOX) Linking...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)$(EMOJI_CHECK) Linked.$(RESET)"
.PHONY : $(NAME)

# Clean object files
clean:
	@echo "$(RED)$(EMOJI_BROOM) Cleaning object files...$(RESET)"
	@rm -f $(OBJS)
	@echo "$(GREEN)$(EMOJI_CHECK) Object files cleaned.$(RESET)"
.PHONY : clean

# Clean object files and binaries
fclean: clean
	@echo "$(RED)$(EMOJI_BROOM) Cleaning binaries...$(RESET)"
	@rm -f $(NAME)
	@if [ -d $(LIBFT_PATH) ]; then \
		$(MAKE) -C $(LIBFT_PATH) fclean; \
	fi
	@if [ -d $(GNL_PATH) ]; then \
		$(MAKE) -C $(GNL_PATH) fclean; \
	fi
	@if [ -d $(MLX_PATH)/build ]; then \
		$(MAKE) -C $(MLX_PATH)/build clean; \
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

LIBS = $(MLX_BIN) $(GNL_BIN) $(LIBFT_BIN) -ldl -lglfw -pthread -lm

LIB_PATH = lib

# ** MLX42 ** #

MLX = MLX42
MLX_REPO = https://github.com/codam-coding-college/MLX42.git
MLX_PATH = $(LIB_PATH)/$(MLX)
MLX_INCLUDE_PATH = $(MLX_PATH)/include/MLX42
MLX_BIN = $(MLX_PATH)/build/libmlx42.a

mlx:
	@if [ ! -d $(MLX_PATH) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Cloning $(MLX)...$(RESET)"; \
		git clone $(MLX_REPO) $(MLX_PATH); \
		rm -rf $(MLX_PATH)/.git; \
		echo "$(GREEN)$(EMOJI_CHECK) $(MLX) cloned...$(RESET)"; \
	fi
	@if [ ! -f $(MLX_BIN) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Compiling $(MLX)...$(RESET)"; \
		cmake $(MLX_PATH) -B $(MLX_PATH)/build && make -C $(MLX_PATH)/build -j4; \
		echo "$(GREEN)$(EMOJI_CHECK) $(MLX) compiled.$(RESET)"; \
	else \
		echo "$(GREEN)$(EMOJI_CHECK) $(MLX) already compiled.$(RESET)"; \
	fi
.PHONY : mlx

# ** Libft ** #

LIBFT = Libft
LIBFT_REPO = https://github.com/sdevsantiago/Libft.git
LIBFT_PATH = $(LIB_PATH)/$(LIBFT)
LIBFT_INCLUDE_PATH = $(LIBFT_PATH)
LIBFT_BIN = $(LIBFT_PATH)/libft.a

libft:
	@if [ ! -d $(LIBFT_PATH) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Cloning $(LIBFT)...$(RESET)"; \
		git clone $(LIBFT_REPO) $(LIBFT_PATH); \
		rm -rf $(LIBFT_PATH)/.git; \
		echo "$(GREEN)$(EMOJI_CHECK) $(LIBFT) cloned...$(RESET)"; \
	fi
	@if [ ! -f $(LIBFT_BIN) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Compiling $(LIBFT)...$(RESET)"; \
		$(MAKE) -C $(LIBFT_PATH) all bonus clean; \
		echo "$(GREEN)$(EMOJI_CHECK) $(LIBFT) compiled.$(RESET)"; \
	else \
		echo "$(GREEN)$(EMOJI_CHECK) $(LIBFT) already compiled.$(RESET)"; \
	fi
.PHONY : libft

# ** get_next_line ** #

GNL = get_next_line
GNL_REPO = https://github.com/sdevsantiago/get_next_line.git
GNL_PATH = $(LIB_PATH)/$(GNL)
GNL_INCLUDE_PATH = $(GNL_PATH)
GNL_BIN = $(GNL_PATH)/get_next_line.a

get_next_line:
	@if [ ! -d $(GNL_PATH) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Cloning $(GNL)...$(RESET)"; \
		git clone $(GNL_REPO) $(GNL_PATH); \
		rm -rf $(GNL_PATH)/.git; \
		echo "$(GREEN)$(EMOJI_CHECK) $(GNL) cloned...$(RESET)"; \
	fi
	@if [ ! -f $(GNL_BIN) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Compiling $(GNL)...$(RESET)"; \
		$(MAKE) -C $(GNL_PATH) all clean; \
		echo "$(GREEN)$(EMOJI_CHECK) $(GNL) compiled.$(RESET)"; \
	else \
		echo "$(GREEN)$(EMOJI_CHECK) $(GNL) already compiled.$(RESET)"; \
	fi
.PHONY : get_next_line
