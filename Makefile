##
## Makefile for  in /home/essian_b/rendu/lemipc
##
## Made by Essiane Abel
## Login   <essian_b@epitech.net>
##
## Started on  Tue Mar 22 21:56:04 2016 Essiane Abel
## Last update Sun Mar 27 23:36:05 2016 Essiane Abel
##

CC	= gcc

NAME	= lemipc

CFLAGS	+= -W -Wall -Wextra
CFLAGS	+= -Iinclude

LDFLAGS	+= -pthread -lm

SRCS	= main.c		\
	  detect.c		\
	  catch.c		\
	  liberathor.c		\
	  game_loop.c		\
	  displayer.c		\
	  getters.c		\
	  init_ipcs.c		\
	  move.c		\
	  movement.c		\
	  msg_types.c		\
	  errors.c		\
	  appear.c

OBJS	= $(SRCS:.c=.o)

RM	= rm -f
PRINTF	= @printf

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
	$(PRINTF) '\033[1;32m> Compiled\033[0m\n'

clean:
	$(RM) $(OBJS)
	$(PRINTF) '\033[1;35m> Directory cleaned\033[0m\n'

fclean: clean
	$(RM) $(NAME)
	$(PRINTF) '\033[1;35m> Remove executable\033[0m\n'

re: fclean all

rer:
	./.sl

.PHONY: all clean fclean re
