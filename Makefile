##
## EPITECH PROJECT, 2023
## B-PSU-400-LYN-4-1-strace-oscar.deschamps
## File description:
## Makefile
##

NAME	=	strace
LD		= 	gcc
SRC		=	$(wildcard src/*.c)
OBJ 	=	$(SRC:.c =.o)
LDFLAGS =	-fno-builtin
CFLAGS 	= 	-f elf

all : $(NAME)

$(NAME) : $(OBJ)
	$(LD) $(OBJ) -o $(NAME) $(LDFLAGS)

clean :
	rm -rf *.o

fclean : clean
	rm -rf $(NAME)

re: fclean all