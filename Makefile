# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcarpent <bcarpent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 13:57:23 by bcarpent          #+#    #+#              #
#    Updated: 2024/05/06 17:39:43 by bcarpent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror -g3

NAME = so_long
LIBFT_DIR = Libft
GNL_DIR = GNL
PRINTF_DIR = Ft_Printf
SO_LONG_DIR = So_Long_srcs
SRCS =	$(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c \
	$(PRINTF_DIR)/ft_printf.c $(PRINTF_DIR)/ft_itoa.c $(PRINTF_DIR)/ft_uitoa.c \
	$(PRINTF_DIR)/ft_putnbrhexa_printf.c $(PRINTF_DIR)/ft_putnbrptr_printf.c \
	$(PRINTF_DIR)/ft_utils_printf.c \
	$(SO_LONG_DIR)/so_long.c $(SO_LONG_DIR)/so_long_map.c $(SO_LONG_DIR)/so_long_utils.c \
	$(SO_LONG_DIR)/so_long_display.c $(SO_LONG_DIR)/so_long_checker.c \
	$(SO_LONG_DIR)/so_long_map_utils.c
LDFLAGS     = -Lminilibx/mlx_Linux -Lminilibx/mlx -L/usr/lib -Imlx_linux -lXext -lX11
LIB         = ml/libmlx.a ml/libmlx_Linux.a

OBJS = ${SRCS:.c=.o}
DEPS = ${OBJS:.o=.d}

GREEN_COLOR = "\033[32m"
CYAN_COLOR = "\033[36m"
BLUE_COLOR = "\033[34m"
X = "\033[0m"
BOLD = "\033[1m"

all: ${NAME}

-include ${DEPS}

${NAME}: ${OBJS}
	@echo $(BOLD)$(GREEN_COLOR)Compiling the following files:$(X)$(CYAN_COLOR)[$(SRCS)]$(X)
	@${CC} $^ $(LIB) $(LDFLAGS) -o ${NAME} 
	@echo $(BOLD)$(GREEN_COLOR)Compilation done.

%.o : %.c
	@${CC} ${FLAGS} -MMD -MP -o $@ -c $< -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(SO_LONG_DIR)

clean :
	@rm -f ${OBJS} ${DEPS}
	@echo $(BOLD)$(GREEN_COLOR)Cleaning the following files: $(X)$(BLUE_COLOR)[$(SRCS)]$(X)
	@echo $(BOLD)$(GREEN_COLOR)Cleaning done.

fclean : clean
	@rm -f ${NAME}

re : fclean all
