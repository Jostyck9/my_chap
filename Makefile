##
## EPITECH PROJECT, 2017
## Main Makefile
## File description:
## Makefile which compile the whole project
##

NAME =	client

SRC =	src/main.c \
		src/arg_management.c \
		src/resolve_hostname.c \
		src/sha256.c \
		src/handshake.c \
		src/connection.c

OBJ =	$(SRC:.c=.o)

INC =	-I ./includes		\

CFLAGS= $(INC) -Wextra -Wall -Werror -Wshadow

LIB =	-lssl -lcrypto

CC =	gcc

all:	$(NAME)

$(NAME):$(OBJ)
	gcc -o $(NAME) $(OBJ) $(LIB) $(CFLAGS)

clean:
	$(RM) -f $(OBJ)

fclean:	clean
	$(RM) -f $(NAME)

re:	fclean all

dbg:	CFLAGS += -g -O0
dbg:	fclean all
