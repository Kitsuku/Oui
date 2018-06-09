//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// PauseMenu functions
//

#include "PauseMenu.hpp"
#include "ResumeButton.hpp"
#include "DisplayCommandButton.hpp"
#include "RulesButton.hpp"
#include "PauseSoundButton.hpp"
#include "SaveButton.hpp"
#include "QuitButton.hpp"

PauseMenu::PauseMenu()
{
	std::unique_ptr<AButton> resume (new ResumeButton);
	std::unique_ptr<AButton> command (new DisplayCommandButton);
	std::unique_ptr<AButton> rules (new RulesButton);
	std::unique_ptr<AButton> sound (new PauseSoundButton);
	std::unique_ptr<AButton> save (new SaveButton);
	std::unique_ptr<AButton> quit (new QuitButton);

	_buttons.push_back(std::move(resume));
	_buttons.push_back(std::move(command));
	_buttons.push_back(std::move(rules));
	_buttons.push_back(std::move(sound));
	_buttons.push_back(std::move(save));
	_buttons.push_back(std::move(quit));
}

PauseMenu::~PauseMenu()
{
}
