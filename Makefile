GRN = \033[1;32m
YEL = \033[0;33m
RED = \033[1;31m
WHT = \033[0m

NAME 	= pipex
FLAGS 	= -Wall -Werror -Wextra
CC		=

OBJ_DIR	= obj_dir
LIBFT	= libft/libft.a

BONUS	= 0

C_FILES_MAND 	= pipex.c \
				find_command_paths.c \
				free_all.c

O_FILES_MAND	= $(patsubst %, $(OBJ_DIR)/%, $(C_FILES_MAND:.c=.o))

all:	make_libft	make_obj_dir	$(NAME)
	@echo "$(GRN)\n --- Done --- $(WHT)"


make_libft:
	@echo "$(YEL)\n --- Making libft.a Library --- $(WHT)"
	make -C ./libft


make_obj_dir:
	@echo "$(YEL)\n --- Making obj_dir Directory --- $(WHT)"
	mkdir -p $(OBJ_DIR)/
	rm outfile && touch outfile


$(OBJ_DIR)/%.o:		%.c
	@echo "$(YEL)\n --- Making .o file --- $(WHT)"
	gcc -g $(FLAGS) -c $< -o $@


$(NAME): $(O_FILES_MAND)
	@echo "$(YEL)\n --- Making the Executable --- $(WHT)"
	gcc $^ $(FLAGS) $(LIBFT) -o $(NAME)

re: fclean
	make

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	cd ./libft && make fclean
	rm -rf pipex
