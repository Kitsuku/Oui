##
## EPITECH PROJECT, 2018
## plazza
## File description:
## makefile
##

CC	=	g++ -g

RM	=	rm -f

NAME	=	indie

SRC	=	src/main.cpp	\
		src/checkDie.cpp	\
		src/getObjectAtPosition.cpp	\
		src/usefullGestionFct.cpp	\
		src/menu/AMenu.cpp	\
		src/menu/MainMenu.cpp	\
		src/menu/MultiMenu.cpp	\
		src/menu/OptionMenu.cpp	\
		src/menu/PauseMenu.cpp	\
		src/menu/PlayMenu.cpp	\
		src/menu/SoloMenu.cpp	\
		src/button/AButton.cpp	\
		src/button/BackGroundMultiButton.cpp	\
		src/button/BackGroundSoloButton.cpp	\
		src/button/DisplayCommandButton.cpp	\
		src/button/ExitButton.cpp	\
		src/button/GroundMultiButton.cpp	\
		src/button/GroundSoloButton.cpp	\
		src/button/LoadButton.cpp	\
		src/button/MultiButton.cpp	\
		src/button/OptionButton.cpp	\
		src/button/PauseSoundButton.cpp	\
		src/button/PlayButton.cpp	\
		src/button/QuitButton.cpp	\
		src/button/ResumeButton.cpp	\
		src/button/ReturnMmButton.cpp	\
		src/button/RulesButton.cpp	\
		src/button/SaveButton.cpp	\
		src/button/SaveGestionButton.cpp	\
		src/button/SoloButton.cpp	\
		src/button/SoundButton.cpp	\
		src/button/StartSoloButton.cpp	\
		src/button/StartMultiButton.cpp	\
		src/graphics/Graphics.cpp	\
		src/graphics/MyEvent.cpp	\
		src/graphics/MyException.cpp	\
		src/map/Map.cpp	\
		src/map/play.cpp	\
		src/objects/AObject.cpp	\
		src/objects/Bomb.cpp	\
		src/objects/Bonus.cpp	\
		src/objects/UnbrWall.cpp	\
		src/objects/Wall.cpp	\
		src/characters/ACharacter.cpp	\
		src/characters/Player.cpp \
		src/characters/IA.cpp
		#src/map/ACharacter_methods.cpp
		#src/map/AObject_methods.cpp

CPPFLAGS	=	-I./include/
CPPFLAGS	+=	-I./include/Menu
CPPFLAGS	+=	-I./include/Button
CPPFLAGS	+=	-I./include/Graphics
CPPFLAGS	+=	-I./include/objects
CPPFLAGS	+=	-I./include/Irrlicht
CPPFLAGS	+=	-I./json-develop/single_include/nlohmann
CPPFLAGS	+=	-I/usr/X11R6/include
CPPFLAGS	+=	-W
CPPFLAGS	+=	-Wall
CPPFLAGS	+=	-Wextra

LIB		=	-L./lib -lIrrlicht
LIB		+=	-L/usr/X11R6/lib -lGL -lXxf86vm -lXext -lX11 -lXcursor

OBJ	=	$(SRC:.cpp=.o)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) $(CPPFLAGS) -o $(NAME) $(LIB)

all:	$(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
