# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mla-rosa <mla-rosa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 13:09:44 by mla-rosa          #+#    #+#              #
#    Updated: 2022/12/20 02:49:53 by mla-rosa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =	ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strncmp.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_strnstr.c\
		ft_atoi.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_striteri.c\
		ft_putchar_fd.c

SRC_BNS = 	ft_lstnew.c\
			ft_lstadd_front.c\
			ft_lstsize.c\
			ft_lstlast.c\
			ft_lstadd_back.c\
			ft_lstdelone.c\
			ft_lstclear.c\
			ft_lstclear.c\
			ft_lstiter.c\
			ft_lstmap.c

OBJ = $(SRC:.c=.o)

OBJ_BNS = $(SRC_BNS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3 -I.

all : $(NAME)

$(NAME) : $(OBJ)
	ar rsc  $(NAME) $(OBJ)

bonus : $(OBJ_BNS)
	ar rsc  $(NAME) $(OBJ_BNS)

clean :
	rm -rf $(OBJ) $(OBJ_BNS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
	
.PHONY : clean fclean all re bonus
