# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julhong <julhong@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/05 22:49:28 by julhong           #+#    #+#              #
#    Updated: 2025/11/06 01:14:31 by julhong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADERS = minsh.h
SRC_DIR = srcs
OBJ_DIR = objs
SRC_BASE = 	_main
SRCS = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_BASE)))
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

CFLAGS = -Wall -Werror -Wextra
LIB_DIRS = -Llibft
LIBS = -lft -lreadline -lncurses
INCLUDES = -I. -Ilibft

ifeq ($(shell uname), Darwin)
 LIB_DIRS += -L/opt/homebrew/opt/readline/lib
 INCLUDES += -I/opt/homebrew/opt/readline/include
endif

all: make_libft $(NAME)

make_libft:
	make -C libft

$(NAME): $(OBJS) libft/libft.a
	cc $(CFLAGS) $(OBJS)	\
	$(LIB_DIRS) $(LIBS)		\
	-o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	cc -c $(CFLAGS) $(INCLUDES) $< -o $@

$(OBJ_DIR):
	mkdir -p $@

bonus: all

.PHONY:	all re fclean clean	\
		make_libft

#Cleanup
re: fclean all

fclean: clean
	rm -rf $(NAME)
	make -C libft fclean

clean:
	rm -rf $(OBJS)
	make -C libft clean
