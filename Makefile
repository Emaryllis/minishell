# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julhong <julhong@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/05 22:49:28 by julhong           #+#    #+#              #
#    Updated: 2026/01/17 22:32:54 by julhong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = srcs

MAIN_SRC_DIR = $(SRC_DIR)/00_main
MAIN_FNAME = _main
MAIN_SRC_BASE =	$(MAIN_FNAME)

LEX_SRC_DIR = $(SRC_DIR)/02_input_lexing
LEX_SRC_BASE =	_lexer		tk_node_data	tk_make_op		lex_utils		\
				tk_cleanup		debug_toks

PARSE_SRC_DIR = $(SRC_DIR)/03_parser
PARSE_SRC_BASE = _parser	pnode_data	 	parse_cmdseg	assert_syntax	\
				ast_cleanup		debug_garbc		debug_ast

EXPN_SRC_DIR = $(SRC_DIR)/04_expans
EXPN_SRC_BASE =	exp1_str_envs	exp2_argv	globbing	exp_utils			\
				debug_expans

EXEC_SRC_DIR = $(SRC_DIR)/05_exec
EXEC_SRC_BASE =	_exec	cmd_handling		external_cmd					\
				run_redirs		exec_cleanup	exec_errs

ENV_SRC_DIR = $(SRC_DIR)/env
ENV_SRC_BASE =	arr_accessors	arr_mutators	arr_validators				\
				dynamic_arr		quick_sort

BUILTIN_SRC_DIR = $(SRC_DIR)/builtins
BUILTIN_SRC_BASE =	cd echo env exit export pwd unset

UTILS_SRC_DIR = $(SRC_DIR)/utils
UTILS_SRC_BASE =	cell parse prompt signal utils

SRCS = \
	$(addprefix $(MAIN_SRC_DIR)/, $(addsuffix .c, $(MAIN_SRC_BASE)))		\
	$(addprefix $(LEX_SRC_DIR)/, $(addsuffix .c, $(LEX_SRC_BASE)))			\
	$(addprefix $(PARSE_SRC_DIR)/, $(addsuffix .c, $(PARSE_SRC_BASE)))		\
	$(addprefix $(EXPN_SRC_DIR)/, $(addsuffix .c, $(EXPN_SRC_BASE)))		\
	$(addprefix $(EXEC_SRC_DIR)/, $(addsuffix .c, $(EXEC_SRC_BASE)))		\
	$(addprefix $(ENV_SRC_DIR)/, $(addsuffix .c, $(ENV_SRC_BASE)))			\
	$(addprefix $(BUILTIN_SRC_DIR)/, $(addsuffix .c, $(BUILTIN_SRC_BASE)))	\
	$(addprefix $(UTILS_SRC_DIR)/, $(addsuffix .c, $(UTILS_SRC_BASE)))

MODULE_DIRS = $(MAIN_SRC_DIR)	\
	$(LEX_SRC_DIR) $(PARSE_SRC_DIR)	$(EXPN_SRC_DIR) $(EXEC_SRC_DIR)	\
	$(ENV_SRC_DIR) $(BUILTIN_SRC_DIR) $(UTILS_SRC_DIR)

vpath %.c $(MODULE_DIRS)

OBJ_DIR = objs
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

DEBUG ?= 0
FSAN ?= 0

CFLAGS = -Wall -Werror -Wextra
LIB_DIRS = -Llibft
LIBS = -lft -lreadline -lncurses
INCLUDES = -I. -Ilibft -Isrcs/ft_libc
HEADERS = minsh.h

ifeq ($(DEBUG), 1)
 CFLAGS += -DDEBUG=1
endif

ifeq ($(FSAN), 1)
 CFLAGS += -g -fsanitize=address
endif

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
