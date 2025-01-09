# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 19:07:42 by sede-san          #+#    #+#              #
#    Updated: 2024/12/30 15:10:04 by sede-san         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ******************************* Output files ******************************* #

# Executable file name
NAME = fdf

# ************************** Compilation variables *************************** #

# Compiler
CC = cc

# Compilation flags
CFLAGS = -Wall -Wextra -Werror -Iinclude -pthread -lm -Ofast

# Linker flags
LDFLAGS = -ldl -lglfw

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

# ***************************** Library paths ******************************** #

# Library path
LIB_PATH = lib

LIBFT_PATH = $(LIB_PATH)/Libft

LIBMLX_PATH = $(LIB_PATH)/MLX42

FT_PRINTF_PATH = $(LIB_PATH)/ft_printf

GET_NEXT_LINE_PATH = $(LIB_PATH)/get_next_line
GET_NEXT_LINE_FILES = get_next_line.c get_next_line_utils.c

# ****************************** Source files ******************************** #

# Source files path
SRC_PATH = src

# Source files
SRC = \
	fdf.c \

# ****************************** Object files ******************************** #

# Object files path
BUILD_PATH = build

# Create object files path
$(shell mkdir -p $(BUILD_PATH))

# Object files
OBJ = $(addprefix $(BUILD_PATH)/, $(SRC:.c=.o))

# Compile object files
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# ********************************* Rules ************************************ #

# Compile all
all: $(NAME)
	@echo "$(YELLOW)$(EMOJI_WRENCH) Compiling...$(RESET)"
	@$(MAKE) $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) libft
	@$(MAKE) ft_printf
	@$(MAKE) get_next_line
	@$(MAKE) mlx
	@$(CC) $(CFLAGS) $(OBJ) $(BUILD_PATH)/libft.a $(BUILD_PATH)/libftprintf.a $(BUILD_PATH)/get_next_line.a $(BUILD_PATH)/libmlx42.a -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)$(EMOJI_CHECK) Compiled.$(RESET)"

# Clean object files
clean:
	@echo "$(RED)$(EMOJI_BROOM) Cleaning object files...$(RESET)"
	@rm -f $(OBJ)
	@echo "$(GREEN)$(EMOJI_CHECK) Object files cleaned.$(RESET)"

# Clean object files and library
fclean: clean
	@echo ""
	@echo "$(RED)$(EMOJI_BOX) Cleaning libraries...$(RESET)"
	@rm -f $(NAME)
	@echo ""
	@$(MAKE) cleanlibft
	@echo ""
	@$(MAKE) cleanft_printf
	@echo ""
	@$(MAKE) cleanget_next_line
	@echo ""
	@$(MAKE) cleanmlx
	@echo ""
	@echo "$(GREEN)$(EMOJI_CHECK) Libraries cleaned.$(RESET)"
	@rm -rf $(BUILD_PATH)

# Recompile
re: fclean all

# Libft rules
libft:
	@echo "$(YELLOW)$(EMOJI_WRENCH) Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_PATH) all > /dev/null
	@cp $(LIBFT_PATH)/libft.a $(BUILD_PATH)
	@echo "$(GREEN)$(EMOJI_CHECK) libft compiled.$(RESET)"

cleanlibft:
	@echo "$(RED)$(EMOJI_BROOM) Cleaning libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_PATH) clean > /dev/null
	@echo "$(GREEN)$(EMOJI_CHECK) libft cleaned.$(RESET)"

relibft: cleanlibft libft

# ft_printf rules
ft_printf:
	@echo "$(YELLOW)$(EMOJI_WRENCH) Compiling ft_printf...$(RESET)"
	@$(MAKE) -C $(FT_PRINTF_PATH) all > /dev/null
	@cp $(FT_PRINTF_PATH)/libftprintf.a $(BUILD_PATH)
	@echo "$(GREEN)$(EMOJI_CHECK) ft_printf compiled.$(RESET)"

cleanft_printf:
	@echo "$(RED)$(EMOJI_BROOM) Cleaning ft_printf...$(RESET)"
	@$(MAKE) -C $(FT_PRINTF_PATH) clean > /dev/null
	@echo "$(GREEN)$(EMOJI_CHECK) ft_printf cleaned.$(RESET)"

reft_printf: cleanft_printf ft_printf

# Get_next_line rules
get_next_line:
	@echo "$(YELLOW)$(EMOJI_WRENCH) Compiling get_next_line...$(RESET)"
	@cd $(GET_NEXT_LINE_PATH) && $(CC) $(CFLAGS) -c $(GET_NEXT_LINE_FILES)
	@ar rcs $(GET_NEXT_LINE_PATH)/get_next_line.a $(GET_NEXT_LINE_PATH)/*.o
	@cp $(GET_NEXT_LINE_PATH)/get_next_line.a $(BUILD_PATH)
	@echo "$(GREEN)$(EMOJI_CHECK) get_next_line compiled.$(RESET)"

cleanget_next_line:
	@echo "$(RED)$(EMOJI_BROOM) Cleaning get_next_line...$(RESET)"
	@rm -f $(GET_NEXT_LINE_PATH)/*.o
	@rm -f $(GET_NEXT_LINE_PATH)/get_next_line.a
	@rm -f $(BUILD_PATH)/get_next_line.a
	@echo "$(GREEN)$(EMOJI_CHECK) get_next_line cleaned.$(RESET)"

reget_next_line: cleanget_next_line get_next_line

# MLX rules
mlx:
	@echo "$(YELLOW)$(EMOJI_WRENCH) Compiling MLX42...$(RESET)"
	@cd $(LIBMLX_PATH) && cmake -B build > /dev/null && cmake --build build -j4 > /dev/null
	@cp $(LIBMLX_PATH)/build/libmlx42.a $(BUILD_PATH)
	@echo "$(GREEN)$(EMOJI_CHECK) MLX42 compiled.$(RESET)"

cleanmlx:
	@echo "$(RED)$(EMOJI_BROOM) Cleaning MLX42...$(RESET)"
	@rm -rf $(LIBMLX_PATH)/build
	@rm -f $(BUILD_PATH)/libmlx42.a
	@echo "$(GREEN)$(EMOJI_CHECK) MLX42 cleaned.$(RESET)"

remlx: cleanmlx mlx

# *********************************** Phony ********************************** #

.PHONY: all clean fclean re libft cleanlibft fcleanlibft relibft ft_printf cleanft_printf fcleanft_printf reft_printf get_next_line cleanget_next_line reget_next_line mlx cleanmlx remlx $(BUILD_PATH)