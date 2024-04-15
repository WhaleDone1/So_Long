# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcarpent <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 13:57:23 by bcarpent          #+#    #+#              #
#    Updated: 2024/04/15 09:47:45 by bcarpent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror

NAME = so_long
LIBFT_DIR = Libft
GNL_DIR = GNL
SO_LONG_DIR = So_Long_srcs
SRCS =	$(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c \
	$(SO_LONG_DIR)/so_long.c


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
	@${CC} ${FLAGS} -MMD -MP -o $@ -c $< -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(SO_LONG_DIR)

clean :
	@rm -f ${OBJS} ${DEPS}
	@echo $(BOLD)$(GREEN_COLOR)Cleaning the following files: $(X)$(BLUE_COLOR)[$(SRCS)]$(X)
	@echo $(BOLD)$(GREEN_COLOR)Cleaning done.

fclean : clean
	@rm -f ${NAME}

re : fclean all
