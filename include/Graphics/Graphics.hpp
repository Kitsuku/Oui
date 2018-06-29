/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Graphical function
*/

#ifndef GRAPHICS_HPP_
#define GRAPHICS_HPP_

#define MAP_X 13.0
#define MAP_Y 11.0

#define RUN irr::scene::EMAT_RUN
#define ATTACK irr::scene::EMAT_ATTACK
#define STAND irr::scene::EMAT_STAND
#define DEAD irr::scene::EMAT_CROUCH_DEATH
#define DEFAULT_FONT "/res/retro26.png"

#include "MyEvent.hpp"
#include "Bomb.hpp"
#include "Player.hpp"
#include <irrlicht.h>
#include <string>
#include <memory>
#include <list>
#include <vector>

struct PlayerStruct {
	int playerNbr;
	unsigned int index;
	Action oldAction;
	bool isAlive;
};

struct	rect_s {
	float posX;
	float posY;
	float sizeX;
	float sizeY;
};

struct	color_s {
	float opacity;
	float red;
	float green;
	float blue;
};

struct coord_s {
	float	x;
	float	y;
	float	z;
};

using rect_t = struct rect_s;
using color_t = struct color_s;
using coord_t = struct coord_s;

class Graphics
{
public:
	Graphics(const std::string &path);
	~Graphics();
	void	displayMap(const std::vector<ACharacter *> &characters,
			const std::vector<AObject *> &objects,
			const Positions sizeMap);
	void	displayBackground(const std::string background) const;
	void	displayGround(const std::string	&textureName);
	void	displayImage(const std::string textureName,
			const rect_t &imageRec) const;
	void	displayBox(const rect_t &box, const color_t &color) const;
	void	displayText(const std::string &text, const rect_t &rectText,
			const color_t &color);
	bool	begin(void) const;
	bool	end(void);
	const MyEvent	&getEventReceiver(void) const;
	const std::string	&getPath() const;
	const std::vector<irr::SEvent::SJoystickEvent> &getController(void)
			const;
	void	reset();
private:
	void	initAttribut();
	void	displayCharacter(const std::vector<ACharacter *> &character,
			const Positions &sizeMap);
	void	createCharactersNode(const std::vector<ACharacter *> &Char,
			const Positions &sizeMap);
	void	displayFirstCharacter(ACharacter *character,
			const Positions &sizeMap);
	void	createAnimeCharacter(irr::scene::IAnimatedMesh *mesh, const
			std::vector<std::string>&objectPath,
			const coord_t &coord);
	void	displayMovingCharacter(ACharacter *character,
			std::vector<PlayerStruct>::iterator playerIt,
			const Positions &sizeMap);
	void	removePlayerStruct(const std::vector<ACharacter *> &character);
	void	displayAliveCharacter(ACharacter *character,
			std::vector<PlayerStruct>::iterator playerIt,
			const Positions &sizeMap);
	void	displayObject(AObject *object, const Positions &sizeMap);
	void	displayBorder(const std::string &unbWall,
			const Positions &sizeMap);
	void	rotateCharacter(const Action, const Action, const unsigned int);
	void	displayBomb(Bomb *bomb, const Positions &sizeMap);
	void	displayMeshBomb(irr::scene::IAnimatedMesh *mesh,
			const coord_t &coord, const Positions &sizeMap);
	void	displayExplosion(Bomb *bomb, const Positions &sizeMap);
	void	displayVerticalExplosion(Bomb *bomb,
			const Positions &sizeMap);
	void	displayCube(const std::string&image, const Positions &position,
			const Positions &oldSizeMap);
	void	setCube(const std::string &image, irr::scene::ISceneNode *cube);
	const coord_t	createCoord(const Positions &position,
			const Positions &sizeMap) const;
	void	clear_list(void);
	const std::string			&_path;
	std::unique_ptr<irr::IrrlichtDevice>	_device;
	irr::video::IVideoDriver		*_driver;
	irr::scene::ISceneManager		*_smgr;
	irr::gui::IGUIEnvironment		*_guienv;
	irr::gui::IGUIFont			*_font;
	irr::core::dimension2d<irr::u32>	_screenSize;
	MyEvent					_eventReceiver;
	irr::core::array<irr::SJoystickInfo>	_joystickInfo;
	std::list<irr::scene::ISceneNode *> 	_sceneNode;
	std::vector<irr::scene::IAnimatedMeshSceneNode *>	_animatedNode;
	std::vector<irr::scene::IAnimatedMeshSceneNode *>	_characterNode;
	std::vector<PlayerStruct>		_playerStruct;
	unsigned int				_nbrAlive;
	bool	_firstTime;
};

#endif /* !GRAPHICS_HPP_ */
