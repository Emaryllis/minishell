# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julhong <julhong@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 12:51:19 by julhong           #+#    #+#              #
#    Updated: 2025/09/26 00:01:38 by julhong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

LIBFT_SRC_DIR =	srcs/libft_main
LIBFT_SRC_BASE = \
	ft_isalpha	ft_isdigit	ft_isalnum	ft_isprint 	\
	ft_isascii	ft_toupper	ft_tolower	ft_strlen 	\
	ft_strncmp	ft_strlcpy	ft_strlcat	ft_strchr 	\
	ft_strrchr	ft_strnstr	ft_memset	ft_bzero 	\
	ft_memcpy	ft_memmove	ft_memchr	ft_memcmp 	\
	ft_atoi		ft_strdup	ft_calloc				\
	\
	ft_substr		ft_strjoin		ft_strtrim		\
	ft_split 		ft_itoa			ft_strmapi		\
	ft_striteri		ft_putchar_fd	ft_putstr_fd	\
	ft_putendl_fd	ft_putnbr_fd

BONUS_SRC_BASE = \
	ft_lstnew		ft_lstsize		ft_lstadd_front	\
	ft_lstlast		ft_lstadd_back	ft_lstdelone	\
	ft_lstclear		ft_lstiter		ft_lstmap

FTPF_SRC_DIR =	srcs/ftpf
FTPF_SRC_BASE = ft_printf										\
	parse_fmt				print_utils1		print_utils2	\
	printers1_cs_pcent		printers2_diu		printers3_px

GETNL_SRC_DIR =		srcs/getnl
GETNL_SRC_BASE =	get_next_line	get_next_line_utils

ADDONS_SRC_DIR =	srcs/addons
ADDONS_SRC_BASE =	ft_uitoa	ft_atoi_base	ft_isspace		\
	ft_splitvar		ft_csubstr	ft_cleanups		ft_strcpy

SRCS = \
	$(addprefix $(LIBFT_SRC_DIR)/, $(addsuffix .c, $(LIBFT_SRC_BASE)))			\
	$(addprefix $(LIBFT_SRC_DIR)/, $(addsuffix _bonus.c, $(BONUS_SRC_BASE)))	\
	$(addprefix $(GETNL_SRC_DIR)/, $(addsuffix .c, $(GETNL_SRC_BASE)))			\
	$(addprefix $(FTPF_SRC_DIR)/, $(addsuffix .c, $(FTPF_SRC_BASE)))			\
	$(addprefix $(ADDONS_SRC_DIR)/, $(addsuffix .c, $(ADDONS_SRC_BASE)))

OBJ_DIR = objs
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

INCLUDES = .
CFLAGS = -Wall -Werror -Wextra -I$(INCLUDES)

all: $(NAME)

bonus: all

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@echo "ARCHIVED: libft.a"

vpath %.c $(LIBFT_SRC_DIR) $(FTPF_SRC_DIR) $(GETNL_SRC_DIR) $(ADDONS_SRC_DIR)

$(OBJ_DIR)/%.o: %.c libft.h | $(OBJ_DIR)
	@cc -c $(CFLAGS) $< -o $@
	@echo "Compiling libft objs... $(notdir $@)"

$(OBJ_DIR):
	@mkdir -p $@

.PHONY:	all re fclean clean \
		bonus test

#Testing
TEST_BIN = test_exec
TEST_NAME = test_ft_$(TEST)
TEST_SRC_DIR = tests
TEST_SRC = $(TEST_SRC_DIR)/$(TEST_NAME).c
	
test: $(TEST_BIN)
	./$(TEST_BIN)
	$(MAKE) fclean

$(TEST_BIN): $(TEST_SRC) $(NAME)
	cc $(CFLAGS) $< -L. -lft -o $@

#Cleanup
re: fclean all

fclean: clean
	@rm -rf $(NAME) $(TEST_BIN)

clean:
	@rm -rf $(OBJS)
