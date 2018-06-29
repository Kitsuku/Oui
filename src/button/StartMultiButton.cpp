//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// StartButton functions
//

#include "StartMultiButton.hpp"
#include "MainMenu.hpp"
#include "menu.hpp"
#include "Map.hpp"

StartMultiButton::StartMultiButton()
{
	_name = "Start";
}

StartMultiButton::~StartMultiButton()
{
}

void	StartMultiButton::rulesLoading(Graphics *graph)
{
	int     check_a = 0;

	graph->end();
	while (graph->begin() && check_a != 2) {
		const std::vector<irr::SEvent::SJoystickEvent>
			&joystickData = graph->getController();
		check_a = ButtonUnpressed(joystickData, check_a, 0);
		graph->displayBackground("res/Rules.png");
		graph->displayText("PRESS A TO SEE COMMANDS",
				{1400, 60, 200, 30}, {255, 255, 255, 255});
		graph->end();
	}
}

void	StartMultiButton::commandsLoading(Graphics *graph)
{
	int	check_a = 0;

	graph->end();
	while (graph->begin() && check_a != 2) {
		const std::vector<irr::SEvent::SJoystickEvent>
			&joystickData = graph->getController();
		check_a = ButtonUnpressed(joystickData, check_a, 0);
		graph->displayBackground("res/Commands.jpg");
		graph->displayText("PRESS A TO START",
				{1500, 1020, 200, 30}, {255, 255, 255, 255});
		graph->end();
	}
}

void	StartMultiButton::trailer(Graphics *graph)
{
	float	x = 1900;
	float	y = 0;
	int	bomb = 0;
	int	sec = 3;
	int	stop = 0;

	graph->end();
	while (graph->begin() && stop != 100) {
		graph->displayBackground("res/flagstones.jpg");
		if (sec > 0)  {
			graph->displayImage("res/Bomba.png", {x + 500, y + 275, 259, 391});
			graph->displayImage("res/Bomba.png", {x + 500, y - 275, 259, 391});
			graph->displayImage("res/Bomba.png", {x - 500, y - 275, 259, 391});
			graph->displayImage("res/Bomba.png", {x - 500, y + 275, 259, 391});
			graph->displayImage("res/Bomba.png", {x, y - 275, 259, 391});
			graph->displayImage("res/Bomba.png", {x, y + 275, 259, 391});
		}
		if (x > 850) {
			x -= 10;
			y += 3;
		} else
			bomb += 1;
		if (x <= 850) {
		graph->displayText(std::to_string(sec), {1450, 350, 30, 30}, {255, 255, 255, 255});
		graph->displayText(std::to_string(sec), {1450, 900, 30, 30}, {255, 255, 255, 255});
		graph->displayText(std::to_string(sec), {450, 350, 30, 30}, {255, 255, 255, 255});
		graph->displayText(std::to_string(sec), {450, 900, 30, 30}, {255, 255, 255, 255});
		graph->displayText(std::to_string(sec), {950, 350, 30, 30}, {255, 255, 255, 255});
		graph->displayText(std::to_string(sec), {950, 900, 30, 30}, {255, 255, 255, 255});
		}
		if (bomb == 50) {
			bomb = 0;
			sec -= 1;
		}
		if (sec <= 0) {
			graph->displayImage("res/burst.png", {1000, 450, 909, 720});
			graph->displayImage("res/burst.png", {1000, -125, 909, 720});
			graph->displayImage("res/burst.png", {500, 450, 909, 720});
			graph->displayImage("res/burst.png", {500, -125, 909, 720});
			graph->displayImage("res/burst.png", {0, 450, 909, 720});
			graph->displayImage("res/burst.png", {0, -125, 909, 720});
			graph->displayImage("res/Bomberman_Title.png", {300, 400, 1280, 335});
			stop += 1;
		}
		graph->end();
	}
}

void	StartMultiButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> main = std::make_unique<MainMenu>();
	Map	map(13, 11, graph->getPath());

	_menu = std::move(main);
	this->rulesLoading(graph);
	this->commandsLoading(graph);
	this->trailer(graph);
	map.generateMap();
	map.generateCharacter(2);
	map.setSpriteGroundAndBackGround();
	map.play(graph);
}
