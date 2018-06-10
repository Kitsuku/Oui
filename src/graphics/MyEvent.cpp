/*
** EPITECH PROJECT, 2018
** Indie studio
** File description:
** Event functions
*/

#include "MyEvent.hpp"

#include <iostream>
MyEvent::MyEvent()
{
	irr::SEvent	initEvent;

	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; i++) {
		_key[i] = false;
	}
	for (unsigned int i = 0; i < NBR_CONTROLLER; i++) {
		_joystickState.push_back(initEvent.JoystickEvent);
	}
}

MyEvent::~MyEvent()
{
}

bool	MyEvent::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		_key[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}
#ifdef WIN32
	for (unsigned int i = 0; i < NBR_CONTROLLER; i++) {
		std::cerr << event.EventType << std::endl;
		if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
		&& event.JoystickEvent.Joystick == i) {
			std::cerr << "Ici" << std::endl;
			_joystickState[i] = event.JoystickEvent;
		}
	}
#else
	for (unsigned int i = 0; i < NBR_CONTROLLER; i++) {
		std::cerr << event.EventType << std::endl;
		if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
			&& event.JoystickEvent.Joystick == i) {
			std::cerr << "Ici" << std::endl;
			_joystickState[i] = event.JoystickEvent;
		}
	}
#endif
	return false;
}

bool	MyEvent::isKeyDown(const irr::EKEY_CODE keyCode) const
{
	return _key[keyCode];
}

const std::vector<irr::SEvent::SJoystickEvent>
&MyEvent::getJoystickState(void) const
{
	return _joystickState;
}

