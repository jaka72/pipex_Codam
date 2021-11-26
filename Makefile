# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jmurovec <jmurovec@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/12 11:57:26 by jmurovec      #+#    #+#                  #
#    Updated: 2021/11/25 14:59:34 by jaka          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

GRN = \033[1;32m
YEL = \033[0;33m
RED = \033[1;31m
WHT = \033[0m

NAME 	= pipex
FLAGS 	= -Wall -Werror -Wextra

OBJ_DIR	= obj_dir
LIBFT	= libft/libft.a

BONNUS	= 0

ifeq ($(BONNUS),0)
	HEADER		= pipex.h
	C_FILES		= pipex.c \
				find_command_paths.c \
				init_data_and_get_commands.c \
				free_all.c
else
	HEADER		= pipex_bonus/pipex_bonus.h
	C_FILES 	= pipex_bonus/find_command_paths_bonus.c \
				pipex_bonus/pipex_bonus.c \
				pipex_bonus/init_data_and_get_commands_bonus.c \
				pipex_bonus/free_all_bonus.c
endif

O_FILES	= $(patsubst %, $(OBJ_DIR)/%, $(C_FILES:.c=.o))


all:	make_libft	make_obj_dir	$(NAME)
	@echo "$(GRN)\n --- Done --- $(WHT)"


make_libft:
	@echo "$(YEL)\n --- Making libft.a Library --- $(WHT)"
	make -C ./libft


make_obj_dir:
	@echo "$(YEL)\n --- Making obj_dir Directory --- $(WHT)"
	mkdir -p $(OBJ_DIR)/ $(OBJ_DIR)/pipex_bonus/

$(OBJ_DIR)/%.o:		%.c	$(HEADER)
	@echo "$(YEL)\n --- Making .o file --- $(WHT)"
	gcc -g $(FLAGS) -c $< -o $@


$(NAME): $(O_FILES)
	@echo "$(YEL)\n --- Making the Executable --- $(WHT)"
	gcc $^ $(FLAGS) $(LIBFT) -o $(NAME)

bonus:
	@echo "$(YEL)\n--- Pipex Bonus, (Bonus == $(BONNUS) --- $(WHITE)"
	@$(MAKE) $(ALL) BONNUS=1

re: fclean
	make

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	cd ./libft && make fclean
	rm -rf pipex
