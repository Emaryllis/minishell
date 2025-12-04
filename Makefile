# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julhong <julhong@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/05 22:49:28 by julhong           #+#    #+#              #
#    Updated: 2025/12/04 16:19:31 by julhong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = srcs

MAIN_SRC_DIR = $(SRC_DIR)/00_main
MAIN_FNAME = _main
MAIN_SRC_BASE =	$(MAIN_FNAME)

# LEX_SRC_DIR = $(SRC_DIR)/02_input_lexing
# LEX_SRC_BASE =	_lexer		token_nodes		lex_utils

# PARSE_SRC_DIR = $(SRC_DIR)/03_parser
# PARSE_SRC_BASE = _parser	parsing_nodes	temp_printast

ENV_SRC_DIR = $(SRC_DIR)/env
ENV_SRC_BASE =	arr_accessors	arr_mutators	arr_validators			\
					dynamic_arr		quick_sort

BUILTIN_SRC_DIR = $(SRC_DIR)/builtins
BUILTIN_SRC_BASE =	cd echo env exit export pwd unset

FTLIBC_SRC_DIR = $(SRC_DIR)/ft_libc
FTLIBC_SRC_BASE =	ft_bzero ft_calloc ft_itoa ft_memcpy ft_split ft_strchr	\
				ft_strcmp ft_strdup ft_strlen ft_strndup					\
				ft_eprintf ft_eprintf_utils

UTILS_SRC_DIR = $(SRC_DIR)/utils
UTILS_SRC_BASE =	cell parse prompt signal utils

SRCS = \
	$(addprefix $(MAIN_SRC_DIR)/, $(addsuffix .c, $(MAIN_SRC_BASE)))		\
	$(addprefix $(ENV_SRC_DIR)/, $(addsuffix .c, $(ENV_SRC_BASE)))			\
	$(addprefix $(BUILTIN_SRC_DIR)/, $(addsuffix .c, $(BUILTIN_SRC_BASE)))	\
	$(addprefix $(FTLIBC_SRC_DIR)/, $(addsuffix .c, $(FTLIBC_SRC_BASE)))	\
	$(addprefix $(UTILS_SRC_DIR)/, $(addsuffix .c, $(UTILS_SRC_BASE)))

MODULE_DIRS = $(MAIN_SRC_DIR) \
	$(ENV_SRC_DIR) $(BUILTIN_SRC_DIR) $(FTLIBC_SRC_DIR) $(UTILS_SRC_DIR)
#$(LEX_SRC_DIR) $(PARSE_SRC_DIR)

vpath %.c $(MODULE_DIRS)

OBJ_DIR = objs
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

CFLAGS = -Wall -Werror -Wextra
LIB_DIRS = -Llibft
LIBS = -lft -lreadline -lncurses
INCLUDES = -I. -Ilibft -Isrcs/ft_libc
HEADERS = minsh.h

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

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	cc -c $(CFLAGS) $(INCLUDES) $< -o $@

$(OBJ_DIR):
	mkdir -p $@

#TESTING ----------------------------------------------------------------------
TEST_NAME = test_exec

TEST_SRC_DIR = $(SRC_DIR)/tests
TEST_SRC_BASE = $(TEST)_test
TEST_SRC = $(TEST_SRC_DIR)/$(TEST_SRC_BASE).c
TEST_OBJ = $(OBJ_DIR)/$(TEST_SRC_BASE).o

test: make_libft $(TEST_NAME)

$(TEST_NAME): $(OBJS) $(TEST_OBJ) libft/libft.a
	cc $(CFLAGS)			\
	$(filter-out $(OBJ_DIR)/$(MAIN_FNAME).o, $(OBJS)) $(TEST_OBJ)	\
	$(LIB_DIRS) $(LIBS)		\
	-o $@

$(OBJ_DIR)/%_test.o: $(TEST_SRC_DIR)/%_test.c $(HEADERS) | $(OBJ_DIR)
	cc -c $(CFLAGS) $(INCLUDES) $< -o $@
#TESTING ----------------------------------------------------------------------

bonus: all

.PHONY:	all re fclean clean	\
		make_libft test

#Cleanup
re: fclean all

fclean: clean
	rm -rf $(NAME) $(TEST_NAME)
	make -C libft fclean

clean:
	find $(OBJ_DIR) -mindepth 1 -delete
	make -C libft clean
