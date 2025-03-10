# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 12:55:34 by guphilip          #+#    #+#              #
#    Updated: 2025/03/10 14:24:02 by guphilip         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS

BLUE				= 		\033[1;34m
GREEN				= 		\033[1;32m
YELLOW				=		\033[1;33m
CYAN				=		\033[1;36m
RESET				= 		\033[0m

# COMMANDS

RM					= /usr/bin/rm -fr
ECHO				= /usr/bin/echo
RM_LINE				= @tput cuu1 && tput el

# FLAGS && COMPILATION

CC 					=	gcc
CFLAGS				=	-Wall -Wextra -Werror -g
IFLAGS				=	-I$(INC_DIR)

# DIRECTORIES

SRC_DIR				=	src
INC_DIR				=	includes
OBJ_DIR				=	obj

# PHILOSOPHERS

SRC_FILES			=	test
SRCS				=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJS				=	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

# TARGET

NAME				=	philo

all:				$(NAME)

clean:
					@$(RM) -r $(OBJ_DIR)

fclean:
					@$(RM) $(NAME)

re: fclean all

norminette:			@norminette $(SRC_DIR) $(INC_DIR) | grep -Ev '^Notice|OK!$$'	\
					&& $(ECHO) -e '\033[1;31mNorminette KO!'
					|| $(ECHO) -e '\033[1;32mNorminette OK!'

.PHONY: all re clean fclean norminette

# PHILOSOPHERS TARGET

$(NAME): $(OBJS)
					@$(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJS)
					@echo "🎉 Executable$(BLUE) $(NAME) $(RESET)created. \n"

$(OBJ_DIR):
					mkdir -p $(OBJ_DIR)

# .O COMPILATION

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
							@echo "⚙️ Compiling $< into $@ ...\n"
							@${RM_LINE}
							@mkdir -p $(dir $@)
							@$(CC) -I$(IFLAGS) $(CFLAGS) -c $< -o $@
							@${RM_LINE}
