/*
** EPITECH PROJECT, 2018
** play.cpp
** File description:
** play method from Map class
*/

#include <iostream>
#include "SaveButton.hpp"
#include "Player.hpp"
#include "Bomb.hpp"
#include "AObject.hpp"
#include "ACharacter.hpp"
#include "Map.hpp"
#include "PauseMenu.hpp"
#include "menu.hpp"

unsigned int	Map::countCharacters()
{
	unsigned int	total = 0;

	for (auto vec_it = _characters.begin(); vec_it != _characters.end();
	vec_it++) {
		if (((*vec_it).get())->getIsDead() == true)
			total += 1;
	}
	return total;
}

AObject	*Map::updateBombPower(Bomb *bomb)
{
	AObject		*actual_object;

	for (auto it = this->_map.begin(); it != this->_map.end(); it++) {
		actual_object = (*it).get();
		if (actual_object->getObjectType() != objectType::BOMB) {
			(static_cast<Bomb *>(bomb))->updatePower(actual_object);
		}
	}
	return bomb;
}

void	Map::updateBombTimer(Bomb *bomb, unsigned int index)
{
	AObject		*actual_object;
	unsigned int	actual_index = 0;

	for (auto it = this->_map.begin(); it != this->_map.end(); it++) {
		actual_object = (*it).get();
		if (actual_index != index &&
		actual_object->getObjectType() == objectType::BOMB) {
			bomb->checkTime();
			bomb->updateTimer(actual_object);
			actual_index += 1;
		}
	}
}

void	Map::playBombs()
{
	AObject		*actual_object;
	unsigned int	index = 0;

	for (auto object_it = this->_map.begin(); object_it != this->_map.end();
	object_it++) {
		actual_object = (*object_it).get();
		if (actual_object->getObjectType() == objectType::BOMB) {
			actual_object = this->updateBombPower(static_cast<Bomb *>(actual_object));
		}
	}
	for (auto it = this->_map.begin(); it != this->_map.end(); it++) {
		actual_object = (*it).get();
		if (actual_object->getObjectType() == objectType::BOMB) {
			this->updateBombTimer(
				static_cast<Bomb *>(actual_object), index);
		}
		index += 1;
	}
}

void	Map::checkBreakWalls(Wall *wall)
{
        AObject	*actual_object;

	for (auto map_it = this->_map.begin(); map_it != this->_map.end();
	map_it++) {
		wall->checkBreak((*map_it).get());
	}
}

void	Map::playWalls()
{
	AObject		*actual_object;
	unsigned int	index = 0;

	for (auto object_it = this->_map.begin(); object_it != this->_map.end();
	object_it++) {
		actual_object = (*object_it).get();
		if (actual_object->getObjectType() == objectType::WALL) {
			checkBreakWalls(static_cast<Wall *>(actual_object));
		}
	}
}

int	Map::startPause(Graphics *graph, int check_a, int check_b, Map *map)
{
	std::unique_ptr<AMenu>	menu_pause (new PauseMenu);
	SaveButton	save_game;
	AMenu		*menu = menu_pause.get();
	unsigned int	ite_button = 0;
	int		check_x = 0;

	graph->end();
	while (menu && graph->begin() && check_b != 2) {
                const std::vector<irr::SEvent::SJoystickEvent>
                        &joystickData = graph->getController();
		ite_button = MoveButtonFromMenu(ite_button, menu, joystickData);
		check_a = ButtonUnpressed(joystickData, check_a, 0);
		check_x = ButtonUnpressed(joystickData, check_x, 2);
		check_b = ButtonUnpressed(joystickData, check_b, 1);
		menu->displayButton(graph, ite_button);
		graph->displayText("PRESS B TO GO TO MENU",
				{1400, 920, 200, 30}, {100, 255, 255, 255});
		graph->displayText("PRESS X TO SAVE THE GAME",
				{1400, 1020, 200, 30}, {100, 255, 255, 255});
		if (check_a == 2) {
			menu->getButton(ite_button)->action(graph);
			menu = menu->getButton(ite_button)->getBMenu();
			ite_button = 0;
			check_a = 0;
		} else if (check_x == 2)
			save_game.save(map);
		graph->end();
	}
	if (check_b == 2)
		return -1;
	return 0;
}

void	Map::removeNbrBombCharacter(AObject *actual_object)
{
	Bomb	*bomb = static_cast<Bomb *>(actual_object);
	int	it = 0;
	ACharacter	*actual_chara;

	for (auto it = _characters.begin(); it != _characters.end(); it++) {
		actual_chara = (*it).get();
		if (actual_chara->getNbrPlayer() ==
		bomb->getNbrPlayer()) {
			actual_chara->removePutBomb();
			return ;
		}
	}
}

void	Map::checkDeleteObjects()
{
	AObject	*actual_object;

	for (auto it = _map.begin(); it != _map.end(); it++) {
		actual_object = (*it).get();
		if (actual_object->getIsDestroyed() == true) {
			if (actual_object->getObjectType() ==
			objectType::BOMB) {
				removeNbrBombCharacter(actual_object);
				this->playWalls();
			}
			_map.erase(it);
			it = _map.begin();
		}
        }
}

void	Map::checkDeleteCharac()
{
	ACharacter	*actual_charac = nullptr;
	std::vector<AObject *>	vec_objects;

	for (auto it = _map.begin(); it != _map.end(); it++)
		vec_objects.push_back((*it).get());
	for (auto it = _characters.begin(); it != _characters.end(); it++) {
		actual_charac = (*it).get();
                //actual_charac->checkBonus(vec_objects);
		actual_charac->checkDeath(vec_objects);
		if (actual_charac->getIsDead() == true &&
		actual_charac->getNbrPutBomb() == 0) {
			_characters.erase(it);
			it = _characters.begin();
		}
	}
}

void 	Map::addNewElem(AObject *newObject)
{
	Bomb	*bomb = static_cast<Bomb *>(newObject);
	std::unique_ptr<AObject>	object(new Bomb(
		bomb->getNbrPlayer(), bomb->getPower("default"),
		bomb->getPos(), bomb->getLivingSprites(),
		bomb->getDyingSprites()));

	_map.push_back(std::move(object));
}

void	Map::giveActionToCharac(const
		std::vector<irr::SEvent::SJoystickEvent> &joystickData)
{
	AObject 	*returnAction = nullptr;
	int 		temp = 0;
	std::vector<AObject *>	vec_objects;

	for (auto it = _map.begin(); it != _map.end(); it++)
		vec_objects.push_back((*it).get());
	for (auto it = _characters.begin(); it != _characters.end(); it++) {
		temp = ((*it).get())->getNbrPlayer();
		if (temp < 0) {
			returnAction = ((*it).get())->defineAction(
				joystickData[0], vec_objects);
		} else {
#ifdef WIN32
			returnAction = ((*it).get())->defineAction(
				joystickData[temp], vec_objects);
#else
			returnAction = ((*it).get())->defineAction(
				joystickData[temp - 1], vec_objects);
#endif
		}
		if (returnAction != nullptr)
			this->addNewElem(returnAction);
	}
}

void	Map::play(Graphics *graph)
{
	AObject		*temp;
	int		check_start = 0;
	int		check_quit = 0;

	graph->end();
	while (graph->begin() && this->countCharacters() != 1 && check_quit != -1) {
		const std::vector<irr::SEvent::SJoystickEvent>
			&joystickData = graph->getController();
		check_start = ButtonUnpressed(joystickData, check_start, 7);
		if (check_start == 2) {
			check_quit = this->startPause(graph, 0, 0, this);
			check_start = 0;
		}
		this->playBombs();
		this->checkDeleteCharac();
		this->giveActionToCharac(joystickData);
		this->checkDeleteObjects();
		graph->displayBackground(_backGround);
		graph->displayGround(_ground);
		graph->displayMap(this->getAllCharacters(), this->getAllObjects(), this->_mapSize);
		graph->end();
	}
	graph->reset();
}

/*int	main()
{
	Positions	bomb_pos;
	Positions	wall_pos;
	Positions	chara_pos;
	Positions	side_wall_pos;
	std::vector<std::string>	vec_sprites;
	std::string	sprites;
	Map	map(1, 1);

	map.generateMap();
	map.generateCharacter(1);
	map.generateCharacter(2);
	map.play();
	wall_pos.x = 0;
	wall_pos.y = 1;
	side_wall_pos.x = 0;
	side_wall_pos.y = 2;
	wall_pos = wall_pos;
	side_wall_pos = side_wall_pos;

	chara_pos.x = 0;
	chara_pos.y = 0;
	bomb_pos.x = 0;
	bomb_pos.y = 5;
	return 0;
}
*/
