# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 19:07:42 by sede-san          #+#    #+#              #
#    Updated: 2024/12/25 03:36:08 by sede-san         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ******************************* Output files ******************************* #

# Executable file name
NAME = fdf

# ************************** Compilation variables *************************** #

# Compiler
CC = cc

# Compilation flags
CFLAGS = -Wall -Wextra -Werror -IiRESETlude -ldl -lglfw -pthread -lm -Ofast

# ****************************** Color variables ****************************** #

# Define color codes
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m # No Color

# ****************************** Library paths ******************************** #

# Library path
LIB_PATH = lib

LIBFT_PATH = $(LIB_PATH)/Libft
LIBMLX_PATH = $(LIB_PATH)/MLX42
FT_PRINTF_PATH = $(LIB_PATH)/ft_printf
GET_NEXT_LINE_PATH = $(LIB_PATH)/get_next_line

# ****************************** Source files ******************************** #

# Source files path
SRC_PATH = src

# Source files
SRC = \
$(SRC_PATH)/fdf.c \

# ****************************** Object files ******************************** #

# Object files path
BUILD_PATH = build

# Object files
OBJ = $(SRC:$(SRC_PATH)/%.c=$(BUILD_PATH)/%.o)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ********************************* Rules ************************************ #

# Compile all
all: $(NAME)

# MLX rules
mlx:
	@echo "$(YELLOW)Compiling MLX42...$(RESET)"
	@cd $(LIBMLX_PATH) && cmake -B build > /dev/null && cmake --build build -j4 > /dev/null
	@mkdir $(BUILD_PATH) && cp $(LIBMLX_PATH)/build/libmlx42.a $(BUILD_PATH)
	@echo "$(GREEN)MLX42 compiled.$(RESET)"

cleanmlx:
	@echo "$(RED)Cleaning MLX42...$(RESET)"
	@cd $(LIBMLX_PATH) && rm -rf build
	@rm -f $(BUILD_PATH)/libmlx42.a
	@echo "$(GREEN)MLX42 cleaned.$(RESET)"

rewmlx: cleanmlx mlx

# Libft rules
libft:
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_PATH) all bonus
	@echo "$(GREEN)libft compiled.$(RESET)"

cleanlibft:
	@echo "$(RED)Cleaning libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_PATH) clean
	@echo "$(GREEN)libft cleaned.$(RESET)"

fcleanlibft:
	@echo "$(RED)Cleaning libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@echo "$(GREEN)libft cleaned.$(RESET)"

relibft: fcleanlibft libft

$(NAME): $(OBJ)
	libft
	cp Libft/libft.a $(NAME)
	ar rcs $(NAME) $(OBJ)
	mv $(NAME) libftprintf.a

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@cd Libft && $(MAKE) clean
	@rm -f $(OBJ)
	@echo "$(GREEN)Object files cleaned.$(RESET)"

# Clean object files and library
fclean: clean
	@echo "$(RED)Cleaning all files...$(RESET)"
	@cd Libft && $(MAKE) fclean
	@rm -f libftprintf.a
	@rm -f $(OBJ)
	@echo "$(GREEN)All files cleaned.$(RESET)"

# Recompile
re: fclean all

# *********************************** Phony ********************************** #

.PHONY = all clean fclean re