CC 			= 	gcc
CFLAGS		= 	-Wall -Wextra -Werror -I.
NAME 		= 	pipex
SRCS 		= 	pipex.c ft_split.c ft_strncmp.c ft_strlen.c ft_strchr.c pipex_utils.c ft_putstr_fd.c perror_exit.c ft_strdup.c
OBJS 		= 	$(SRCS:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re