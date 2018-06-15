//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// StartButton functions
//

#include "StartSoloButton.hpp"
#include "MainMenu.hpp"
#include "menu.hpp"
#include "Map.hpp"

StartSoloButton::StartSoloButton()
{
	_name = "Start";
}

StartSoloButton::~StartSoloButton()
{
}

void	RulesLoading(Graphics *graph)
{
	int	check_a = 0;

	graph->end();
	while (graph->begin() && check_a != 2) {
                const std::vector<irr::SEvent::SJoystickEvent>
                        &joystickData = graph->getController();
                check_a = ButtonUnpressed(joystickData, check_a, 0);
                graph->displayBackground("res/Rules.png");
                graph->displayText("PRESS A TO SEE COMMANDS",
                                {1400, 60, 200, 30}, {100, 255, 255, 255});
                graph->end();
        }
}

void	CommandsLoading(Graphics *graph)
{
	int	check_a = 0;

	graph->end();
	while (graph->begin() && check_a != 2) {
                const std::vector<irr::SEvent::SJoystickEvent>
                        &joystickData = graph->getController();
                check_a = ButtonUnpressed(joystickData, check_a, 0);
                graph->displayBackground("res/Commands.jpg");
                graph->displayText("PRESS A TO START",
                                {1500, 1020, 200, 30}, {100, 255, 255, 255});
                graph->end();
        }
}

void	StartSoloButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> main (new MainMenu);
	Map	map(1, 1);

	_menu = std::move(main);
	RulesLoading(graph);
	CommandsLoading(graph);
	map.generateMap();
	map.generateCharacter(1);
	map.setSpriteGroundAndBackGround();
	map.play(graph);
}
