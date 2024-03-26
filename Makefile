# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcarpent <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 13:57:23 by bcarpent          #+#    #+#              #
#    Updated: 2024/03/21 13:58:09 by bcarpent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror

NAME = push_swap
LIBFT_DIR = Libft
SO_LONG_DIR = So_Long_srcs
PRINTF_DIR = Printf
SRCS =	$(LIBFT_DIR)/ft_atol.c $(LIBFT_DIR)/ft_split.c \
	$(PUSH_SWAP_DIR)/swap.c $(PUSH_SWAP_DIR)/push.c $(PUSH_SWAP_DIR)/rotate.c \
	$(PUSH_SWAP_DIR)/reverse_rotate.c $(PUSH_SWAP_DIR)/push_swap.c $(PUSH_SWAP_DIR)/push_swap_utils.c\
	$(PUSH_SWAP_DIR)/prepare_move_a.c $(PUSH_SWAP_DIR)/prepare_move_b.c \
	$(PUSH_SWAP_DIR)/sort.c $(PUSH_SWAP_DIR)/push_swap_free.c $(PUSH_SWAP_DIR)/push_swap_utils_2.c\
	$(PRINTF_DIR)/ft_printf.c $(PRINTF_DIR)/ft_utils_printf.c $(PRINTF_DIR)/ft_putnbrptr_printf.c \
	$(PRINTF_DIR)/ft_putnbrhexa_printf.c $(PRINTF_DIR)/ft_itoa.c $(PRINTF_DIR)/ft_uitoa.c


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
	@${CC} ${FLAGS} -o ${NAME} ${OBJS}
	@echo $(BOLD)$(GREEN_COLOR)Compilation done.

%.o : %.c
	@${CC} ${FLAGS} -MMD -MP -o $@ -c $< -I$(LIBFT_DIR) -I$(PUSH_SWAP_DIR) -I$(PRINTF_DIR)

clean :
	@rm -f ${OBJS} ${DEPS}
	@echo $(BOLD)$(GREEN_COLOR)Cleaning the following files: $(X)$(BLUE_COLOR)[$(SRCS)]$(X)
	@echo $(BOLD)$(GREEN_COLOR)Cleaning done.

fclean : clean
	@rm -f ${NAME}

re : fclean all
