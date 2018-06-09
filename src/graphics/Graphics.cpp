/*
** EPITECH PROJECT, 2018
** Indie studio
** File description:
** Graphical function
*/

#include "Graphics.hpp"
#include "MyException.hpp"
#include <iostream>

Graphics::Graphics(const std::string &path): _path(path)
{
	irr::IrrlichtDevice	*tmpDevice = irr::createDevice(irr::video::
				EDT_NULL);
	if (!tmpDevice) {
		throw MyException("Can't create a device");
	}
/* 	_device = irr::createDevice(irr::video::EDT_BURNINGSVIDEO,
	tmpDevice->getVideoModeList()->getDesktopResolution(), 16, true,
	false, false, &_eventReceiver); */
	_device = irr::createDevice(irr::video::EDT_BURNINGSVIDEO, irr::core::dimension2d< irr::u32 >(500, 500), 16,
			false, false, false, &_eventReceiver);
	tmpDevice->drop();
	if (!_device) {
		throw MyException("Can't create a device");
	}
	if (!(_device->activateJoysticks(_joystickInfo))) {
		throw MyException("No Joysticks connected");
	}
	_driver = _device->getVideoDriver();
	_smgr = _device->getSceneManager();
	_smgr->addCameraSceneNode(0, irr::core::vector3df(0,30,-40), irr::core::vector3df(0,5,0));
	_screenSize = _driver->getScreenSize();
}

Graphics::~Graphics()
{
	_device->drop();
}

void			Graphics::displayBackground(const std::string
			textureName) const
{
	std::string			fullPath = _path + textureName;
	irr::core::rect< irr::s32 >	rectTexture(0 , 0, _screenSize.Width,
					_screenSize.Height);

	_driver->draw2DImage(_driver->getTexture(fullPath.c_str()),
	rectTexture, rectTexture);
}

void			Graphics::displayGround(const std::string
			textureName, const pos_t &sizeMap) const
{
	std::string			fullPath = _path + textureName;
	irr::core::rect< irr::s32 >	rectTexture(0 , 0, sizeMap.x,
					sizeMap.y);

	_driver->draw2DImage(_driver->getTexture(fullPath.c_str()),
	irr::core::position2d<irr::s32>(50, 50), rectTexture);
}

const std::vector<irr::SEvent::SJoystickEvent>
&Graphics::getController(void) const
{
	return _eventReceiver.getJoystickState();
}

bool			Graphics::run()
{
	pos_t	size_map = {500, 500};
	//const std::vector<irr::SEvent::SJoystickEvent> & joystickData = _eventReceiver.getJoystickState();
	if (_device->run()) {
		_driver->beginScene();
 		_smgr->drawAll();
		/*guienv->drawAll(); */
		displayBackground("/res/Background/background.jpg");
		_driver->endScene();
		if (_eventReceiver.isKeyDown(irr::KEY_ESCAPE)) {
			_device->closeDevice();
		}
		return true;
	}
	return false;
}
