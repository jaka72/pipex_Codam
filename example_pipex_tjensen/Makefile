# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 18:33:16 by tjensen           #+#    #+#              #
#    Updated: 2021/10/29 10:55:46 by tjensen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

LIBFTDIR	= libs/libft
INCLUDES	= -I./include -I./$(LIBFTDIR)/include
LIBRARIES	= -L./$(LIBFTDIR)/ -lft

SDIR		= src
SRCS		= pipex.c utils.c pipex_pipes.c pipex_child.c pipex_cmd.c
ODIR		= obj
OBJS		= $(addprefix $(ODIR)/, $(SRCS:.c=.o))

# COLORS
COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

# **************************************************************************** #
#						SYSTEM SPECIFIC SETTINGS							   #
# **************************************************************************** #

UNAME_S	= $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CFLAGS += -D LINUX -Wno-unused-result -Wno-maybe-uninitialized
endif

# **************************************************************************** #
#									RULES									   #
# **************************************************************************** #

.PHONY: all
all: $(NAME)

.PHONY: debug
debug: CFLAGS += -O0 -DDEBUG -g
debug: all

.PHONY: release
release: fclean
release: CFLAGS	+= -O2 -DNDEBUG
release: all

header:
	@printf "%b" "###############################################\n"
	@printf "%-14b %b" "$(WARN_COLOR)#######" "$(NAME)$(NO_COLOR)\n"

# Linking
.PHONY: $(NAME)
$(NAME): libft header prep $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBRARIES)
	@printf "%-14b %-42b %b" "$(OK_COLOR)=======" "$(OK_COLOR)$(NAME)" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

# Compiling
.PHONY: $(ODIR)/%.o
$(ODIR)/%.o: $(SDIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "%-57b %b" "$(COM_COLOR)compile $(OBJ_COLOR)$@" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

.PHONY: libft
libft:
ifneq ($(MAKECMDGOALS), $(filter $(MAKECMDGOALS), $(NAME) $(CHECKER)))
	@make -C $(LIBFTDIR) $(MAKECMDGOALS) --silent
else
	@make -C $(LIBFTDIR) --silent
endif

.PHONY: prep
prep:
	@mkdir -p $(ODIR)

.PHONY: clean
clean: libft header
	@$(RM) -r $(ODIR) $(CHECK_ODIR)
	@printf "%-50b %b" "$(COM_COLOR)clean" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

.PHONY: fclean
fclean: libft header clean
	@$(RM) $(NAME) $(CHECKER)
	@$(RM) -r src/$(NAME) src/*.dSYM
	@printf "%-50b %b" "$(COM_COLOR)fclean" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

.PHONY: re
re: libft fclean all

.PHONY: bonus
bonus: all
