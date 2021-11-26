# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jmurovec <jmurovec@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/29 18:54:57 by jmurovec      #+#    #+#                  #
#    Updated: 2021/11/24 15:53:20 by jmurovec      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a

MANDATORY       = ft_split.c \
				ft_strncmp.c \
				ft_strjoin.c \
				ft_strlen.c \
				ft_putstr_fd.c \
				ft_putnbr_fd.c

OBJS			= $(MANDATORY:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.
HEADER			= libft.h

.c.o:
				${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

all:			$(NAME)

$(NAME):		$(OBJS) $(HEADER)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
