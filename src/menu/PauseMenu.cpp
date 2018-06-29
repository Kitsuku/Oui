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
	std::unique_ptr<AButton> resume = std::make_unique<ResumeButton>();
	std::unique_ptr<AButton> command = std::make_unique<DisplayCommandButton>();
	std::unique_ptr<AButton> rules = std::make_unique<RulesButton>();
	std::unique_ptr<AButton> sound = std::make_unique<PauseSoundButton>();

	_buttons.push_back(std::move(resume));
	_buttons.push_back(std::move(command));
	_buttons.push_back(std::move(rules));
	_buttons.push_back(std::move(sound));
}

PauseMenu::~PauseMenu()
{
}
