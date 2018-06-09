/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Graphical function
*/

#ifndef GRAPHICS_HPP_
	#define GRAPHICS_HPP_

	#include <irrlicht.h>
	#include <string>
	#include "MyEvent.hpp"

struct	pos_s {
	float x;
	float y;
};

using pos_t = struct pos_s;

class Graphics
{
		public:
			Graphics(const std::string &path);
			~Graphics();
			void				displayBackground(const
							std::string) const;
			void				displayGround(const
							std::string
							textureName, const
							pos_t &sizeMap) const;
			bool				run();
			const std::vector<irr::SEvent::SJoystickEvent>
							&getController(void)
							const;
		private:
			const std::string			&_path;
			irr::IrrlichtDevice			*_device;
			irr::video::IVideoDriver		*_driver;
			irr::scene::ISceneManager		*_smgr;
			irr::core::dimension2d<irr::u32>	_screenSize;
			MyEvent					_eventReceiver;
			irr::core::array<irr::SJoystickInfo>	_joystickInfo;
};

#endif /* !GRAPHICS_HPP_ */
