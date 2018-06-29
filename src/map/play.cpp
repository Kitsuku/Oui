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
	auto		vec_it = _characters.begin();

	while (vec_it != _characters.end()) {
		if (((*vec_it).get())->getIsDead() == false)
			total += 1;
		vec_it++;
	}
	return total;
}

AObject	*Map::updateBombPower(AObject *bomb)
{
	AObject		*actual_object = nullptr;

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
	AObject		*actual_object = nullptr;
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
	AObject		*actual_object = nullptr;
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
	for (auto map_it = this->_map.begin(); map_it != this->_map.end();
	map_it++) {
		if ((*map_it) != nullptr && wall != nullptr) {
			wall->checkBreak(map_it->get());
		}
	}
	if (wall->getIsDestroyed() == true) {
		this->AddBonus(static_cast<AObject *>(wall));
	}
}

void	Map::playWalls()
{
	AObject		*actual_object = nullptr;
	unsigned int	index = 0;

	for (auto object_it = this->_map.begin(); object_it != this->_map.end();
	object_it++) {
		actual_object = (*object_it).get();
		if (actual_object != nullptr &&
		actual_object->getObjectType() == objectType::WALL) {
			checkBreakWalls(static_cast<Wall *>(actual_object));
		}
	}
}

int	Map::startPause(Graphics *graph, int check_b, int check_a, Map *map)
{
	std::unique_ptr<AMenu>	menu_pause = std::make_unique<PauseMenu>();
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

void	Map::gameOverScreen(Graphics *graph)
{
	int	check_a = 0;

	graph->end();
	while (graph->begin() && check_a != 2) {
		const std::vector<irr::SEvent::SJoystickEvent>
			&joystickData = graph->getController();
		check_a = ButtonUnpressed(joystickData, check_a, 0);
		if (((_characters.at(0)).get())->getNbrPlayer() > 0) {
			graph->displayText("PLAYER ", {890, 820, 100, 30}, {255, 255, 255, 255});
			graph->displayText(std::to_string(_characters.at(0).get()->getNbrPlayer()),
					   {1030, 820, 10, 30}, {255, 255, 255, 255});
			graph->displayText(" HAS WON THE GAME", {1050, 820, 200, 30},
					   {255, 255, 255, 255});
		} else
			graph->displayText("IA WON THE GAME YOU ARE SO BAD ", {890, 820, 300, 30},
					   {255, 255, 255, 255});
		graph->displayText("PRESS A TO GO TO MENU",
				   {1400, 920, 200, 30}, {255, 255, 255, 255});
		graph->displayImage("/res/gameOver.png", {400, 100, 1024, 718});
		graph->end();
	}
}

void	Map::removeNbrBombCharacter(AObject *actual_object)
{
	Bomb	*bomb = static_cast<Bomb *>(actual_object);
	int	it = 0;
	ACharacter	*actual_chara = nullptr;

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
	AObject		*actual_object = nullptr;
	Bomb		*casting = nullptr;

	for (auto it = _map.begin(); it != _map.end(); it++) {
		actual_object = (*it).get();
		if (actual_object != nullptr &&
		actual_object->getIsDestroyed() == true) {
			if (actual_object->getObjectType() == objectType::BOMB) {
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
	objectType	type = objectType::BOMBUP;
	std::string	spritePath = "";

	if (actual_object != nullptr &&
	actual_object->getObjectType() == objectType::WALL) {
		random = (1 + std::rand()/(100 + 1u)/6) %100;
		if (actual_object->getIsDestroyed() == true && random >= 60) {
			cpy.x = (actual_object->getPos()).x;
			cpy.y = (actual_object->getPos()).y;
			if (random >= 95) {
				type = objectType::WALLPASS;
				spritePath = "res/wallPass.png";
			} else if (random >= 85) {
				type = objectType::BOMBUP;
				spritePath = "res/bombUp.png";
			} else if (random >= 70) {
				type = objectType::FIREUP;
				spritePath = "res/fireUp.png";
			} else if (random >= 60) {
				type = objectType::SPEEDUP;
				spritePath = "res/speedUp.png";
			}
			_bonus.push_back({cpy, spritePath, type});
		}
	}
}

void	Map::checkDeleteCharacWithoutBombCheck()
{
	ACharacter	*actual_charac = nullptr;
	std::vector<AObject *>	vec_objects;

	for (auto it = _map.begin(); it != _map.end(); it++)
		vec_objects.push_back((*it).get());
	for (auto it = _characters.begin(); it != _characters.end(); it++) {
		actual_charac = (*it).get();
		actual_charac->checkPlayerDeath(vec_objects);
		if (actual_charac->getIsDead() == true) {
			_characters.erase(it);
			it = _characters.begin();
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
		actual_charac->checkPlayerDeath(vec_objects);
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
	std::unique_ptr<AObject>	object = std::make_unique<Bomb>(
		bomb->getNbrPlayer(), bomb->getPower("default"),
		bomb->getPos(), bomb->getLivingSprites(),
		bomb->getDyingSprites());

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
				joystickData[temp - 1], vec_objects);
		}
		if (returnAction != nullptr)
			this->addNewElem(returnAction);
	}
}

void	Map::play(Graphics *graph)
{
	int		check_start = 0;
	int		check_quit = 0;

	graph->end();
	while (graph->begin() && this->countCharacters() > 1 && check_quit != -1) {
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
		if (_bonus.empty() == false) {
			for (auto bonus = _bonus.begin(); bonus != _bonus.end(); bonus++)
				_map.push_back(std::make_unique<Bonus>((*bonus)));
			_bonus.clear();
		}
		graph->displayBackground(_backGround);
		graph->displayGround(_ground);
		graph->displayMap(this->getAllCharacters(), this->getAllObjects(), this->_mapSize);
		graph->end();
	}
	this->checkDeleteCharacWithoutBombCheck();
	if (this->countCharacters() == 1)
		this->gameOverScreen(graph);
	graph->reset();
}
