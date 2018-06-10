/*
** EPITECH PROJECT, 2018
** play.cpp
** File description:
** play method from Map class
*/

#include <iostream>
#include "Player.hpp"
#include "Bomb.hpp"
#include "Wall.hpp"
#include "Bonus.hpp"
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
		if (((*vec_it).get())->getIsDead() != true)
			total += 1;
	}
	return total;
}

AObject	*Map::updateBombPower(AObject *bomb)
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
			actual_object = this->updateBombPower(actual_object);
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
	AObject		*actual_object;

	for (auto map_it = this->_map.begin(); map_it != this->_map.end();
	map_it++) {
		wall->checkBreak((*map_it).get());
		this->AddBonus(actual_object);
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

void	Map::startPause(Graphics *graph)
{
	std::unique_ptr<AMenu>	menu_pause (new PauseMenu);
	AMenu		*menu = menu_pause.get();
	unsigned int	ite_button = 0;
	int		check_a = 0;

	graph->end();
	while (menu && graph->begin()) {
                const std::vector<irr::SEvent::SJoystickEvent>
                        &joystickData = graph->getController();
		ite_button = MoveButtonFromMenu(ite_button, menu, joystickData);
		check_a = ButtonUnpressed(joystickData, check_a, 0);
		menu->displayButton(graph, ite_button);
		if (check_a == 2) {
			menu->getButton(ite_button)->action(graph);
			menu = menu->getButton(ite_button)->getBMenu();
			ite_button = 0;
			check_a = 0;
		}
		graph->end();
	}
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
	AObject		*actual_object;
	Bomb		*casting;

	for (auto it = _map.begin(); it != _map.end(); it++) {
		actual_object = (*it).get();
		if (actual_object->getIsDestroyed() == true) {
			if (actual_object->getObjectType() ==
			objectType::BOMB) {
				casting = static_cast<Bomb *>(actual_object);
				if (casting->getDelayDead() > 50) {
					removeNbrBombCharacter(actual_object);
					this->playWalls();
					_map.erase(it);
					it = _map.begin();
				} else {
					casting->addDelayDead();
				}
			} else {
				_map.erase(it);
				it = _map.begin();
			}
		}
	}
}

void	Map::AddBonus(AObject *actual_object)
{
	Positions	cpy = {0, 0};
	int		random = 0;
	objectType	type = objectType::BOMB;
	std::string	spritePath = "";

	if (actual_object->getObjectType() == objectType::WALL) {
		random = (1 + std::rand()/(100 + 1u)/6) %100;
		if (actual_object->getIsDestroyed() == true && random >= 70) {
			cpy.x = (actual_object->getPos()).x;
			cpy.y = (actual_object->getPos()).y;
			if (random >= 90) {
				type = objectType::BOMBUP;
				spritePath = "res/bombUp.png";
			}
			else if (random >= 80) {
				type = objectType::WALLPASS;
				spritePath = "res/wallPass.png";
			}
			else if (random >= 70) {
				type = objectType::FIREUP;
				spritePath = "res/fireUp.png";
			}
			std::unique_ptr<AObject>	newBonus(new Bonus(cpy, spritePath, type));
			this->_map.push_back(std::move(newBonus));
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
		actual_charac->checkBonus(vec_objects);
		actual_charac->checkDeath(vec_objects);
		if (actual_charac->getIsDead() == true &&
		actual_charac->getNbrPutBomb() == 0 &&
		actual_charac->getDelayDead() > 1) {
			_characters.erase(it);
			it = _characters.begin();
		} else if (actual_charac->getIsDead() == true &&
		actual_charac->getNbrPutBomb() == 0) {
			actual_charac->addDelayDead();
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
		returnAction = nullptr;
		temp = ((*it).get())->getNbrPlayer();
		if (!(((*it).get())->getIsDead()) && temp < 0) {
			returnAction = ((*it).get())->defineAction(
				joystickData[0], vec_objects);
		} else if (!(((*it).get())->getIsDead())) {
			returnAction = ((*it).get())->defineAction(
				joystickData[0], vec_objects);
		}
		if (returnAction != nullptr)
			this->addNewElem(returnAction);
	}
}

void	Map::play(Graphics *graph)
{
	int		check_start = 0;

	graph->end();
	while (graph->begin() && this->countCharacters() > 1) {
		const std::vector<irr::SEvent::SJoystickEvent>
			&joystickData = graph->getController();
		check_start = ButtonUnpressed(joystickData, check_start, 7);
		if (check_start == 2) {
			this->startPause(graph);
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
