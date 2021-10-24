# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jmurovec <jmurovec@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/29 18:54:57 by jmurovec      #+#    #+#                  #
#    Updated: 2020/11/29 19:28:43 by jmurovec      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a

MANDATORY       = ft_bzero.c ft_memset.c ft_memchr.c ft_calloc.c ft_memcpy.c \
				ft_memccpy.c ft_memmove.c ft_memcmp.c ft_strlen.c \
				ft_strdup.c ft_strlcpy.c ft_strchr.c ft_strrchr.c \
				ft_strnstr.c ft_strncmp.c ft_isalpha.c ft_isalnum.c \
				ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
				ft_strmapi.c ft_substr.c ft_strjoin.c ft_strtrim.c \
				ft_split.c ft_itoa.c ft_putstr_fd.c ft_putendl_fd.c \
				ft_putnbr_fd.c ft_strlcat.c ft_atoi.c ft_isdigit.c \
				ft_putchar_fd.c
OBJS			= $(MANDATORY:.c=.o)

BONUS           = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
				ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c

BONUS_OBJS		= $(BONUS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.

.c.o:
				${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)
so:
				gcc -fPIC -Wall -Werror -Wextra -c libft.h $(MANDATORY) $(BONUS)
				gcc -shared -o libft.so $(OBJS) $(BONUS_OBJS)

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

bonus:			$(OBJS) $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY:			all clean fclean re bonus
