/*
** EPITECH PROJECT, 2018
** Indie studio
** File description:
** Event functions
*/

#ifndef MYEVENT_HPP_
#define MYEVENT_HPP_

#define NBR_CONTROLLER 2

#include <irrlicht.h>
#include <vector>

class MyEvent: public irr::IEventReceiver
{
public:
	MyEvent();
	~MyEvent();
	bool	isKeyDown(const irr::EKEY_CODE keyCode) const;
	bool	OnEvent(const irr::SEvent& event);
	const std::vector<irr::SEvent::SJoystickEvent> &getJoystickState(void)
		const;
private:
	bool	_key[irr::KEY_KEY_CODES_COUNT];
	std::vector<irr::SEvent::SJoystickEvent>	_joystickState;
};

#endif /* !MYEVENT_HPP_ */
