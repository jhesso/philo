# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/13 15:49:11 by jhesso            #+#    #+#              #
#    Updated: 2023/07/13 16:47:58 by jhesso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address
SRC_PATH	=	src/
OBJ_PATH	=	obj/
SRC			=	main.c utils.c validation.c error.c
SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
OBJ			=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(OBJ_PATH), $(OBJ))
INCS		=	-I includes/

# pretty colors for the messages
GREEN			=	\033[0;32m
RED				=	\033[0;31m
BLUE			=	\033[0;34m
RESET			=	\033[0m

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@cc $(CFLAGS) -c $< -o $@ $(INCS)

$(NAME): $(OBJS)
	@echo "$(BLUE)Compiling $(NAME)$(RESET)"
	@cc $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)done$(RESET)"

clean:
	@echo "$(RED)removing object files$(RESET)"
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@echo "$(RED)cleaning all compiled stuff.. :)$(RESET)"
	@/bin/rm -rf $(NAME)
	@echo "$(GREEN)done$(RESET)"

re: fclean all

.PHONY: all clean fclean re
