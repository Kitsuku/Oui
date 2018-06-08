##
## EPITECH PROJECT, 2018
## Makefile Save
## File description:
## 
##

NAME	=	my_save

SRC	=	src/main.cpp	\
		src/ACharacter_methods.cpp	\
		src/AObject_methods.cpp		\
		src/Map.cpp

OBJ	=	$(SRC:.cpp=.o)

GPP	=	g++

CXXFLAGS	=	-I./include -I./include/characters -I./include/objects -I./json-develop/single_include/nlohmann
CXXFLAGS	+=	-W -Wall -Werror -Wextra

RM	=	rm -f

$(NAME):	$(OBJ)
	$(GPP) $(OBJ) -o $(NAME)

all:		$(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re


