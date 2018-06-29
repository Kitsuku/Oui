/*
** EPITECH PROJECT, 2018
** Indie studio
** File description:
** Graphical function
*/

#include "Graphics.hpp"
#include "MyException.hpp"
#include <iostream>
#include <ctime>

Graphics::Graphics(const std::string &path): _path(path), _nbrAlive(0)
{
	std::unique_ptr<irr::IrrlichtDevice>	tmpDevice =
		std::unique_ptr<irr::IrrlichtDevice>(
		irr::createDevice(irr::video::EDT_NULL));

	if (!tmpDevice) {
		throw MyException("Can't create a device");
	}
	_firstTime = true;
	_device = std::unique_ptr<irr::IrrlichtDevice>(
	irr::createDevice(irr::video::EDT_OPENGL,
	tmpDevice->getVideoModeList()->getDesktopResolution(), 16, true,
	false, false, &_eventReceiver));
	if (!_device) {
		throw MyException("Can't create a device");
	}
	if (!(_device->activateJoysticks(_joystickInfo))) {
		throw MyException("No Joysticks connected");
	}
	initAttribut();
}

Graphics::~Graphics()
{
}

void	Graphics::displayMap(const std::vector<ACharacter *> &characters,
		const std::vector<AObject *> &objects, const Positions sizeMap)
{
	std::string			unbrWall;

	if (!_firstTime) {
		displayCharacter(characters, sizeMap);
	} else {
		createCharactersNode(characters, sizeMap);		
		_firstTime = false;
	}
	for (auto it = _playerStruct.begin(); it != _playerStruct.end(); it++) {
		if (it->isAlive && _characterNode[it->index]) {
			_characterNode[it->index]->setVisible(true);
		}
	}
	for (auto it = objects.begin(); it != objects.end(); it++) {
		displayObject((*it), sizeMap);
	}
	for (auto it = objects.begin(); it != objects.end(); it++) {
		if ((*it)->getObjectType() == UNBRWALL) {
			unbrWall = _path + (*it)->getLivingSprites();
			break;
		}
	}
	displayBorder(unbrWall, sizeMap);
}

void	Graphics::displayBackground(const std::string textureName) const
{
	std::string			fullPath = _path + textureName;
	irr::core::rect<irr::s32>	rectTexture(0 , 0, _screenSize.Width,
						_screenSize.Height);

	_driver->draw2DImage(_driver->getTexture(fullPath.c_str()),
	rectTexture, rectTexture);
}

void	Graphics::displayGround(const std::string &textureName)
{
	const std::string		fullPath = _path + textureName;
	irr::scene::ISceneNode		*cube = _smgr->addCubeSceneNode(
					MAP_X);
	const double			scaleY = MAP_Y / MAP_X;

	if (cube)
	{
		cube->setPosition(irr::core::vector3df(0, 0, MAP_X));
		cube->setRotation(irr::core::vector3df(11, 0, 0));
		cube->setScale(irr::core::vector3df(1.05, scaleY + 0.05, 0));
		cube->setMaterialTexture(0,
		_driver->getTexture(fullPath.c_str()));
		cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		_sceneNode.push_back(cube);
	}
}

void	Graphics::displayImage(const std::string textureName,
		const rect_t &imageRect) const
{
	std::string			fullPath = _path + textureName;
	irr::core::rect<irr::s32>	sourceRect(0 , 0,  imageRect.sizeX,
					imageRect.sizeY);
	irr::core::rect<irr::s32>	destRect(imageRect.posX, imageRect.posY,
					imageRect.posX + imageRect.sizeX,
					imageRect.posY + imageRect.sizeY);

	irr::video::ITexture* images = _driver->getTexture(fullPath.c_str());
	_driver->draw2DImage(images, irr::core::position2d<irr::s32>(imageRect.posX,imageRect.posY), sourceRect, 0, irr::video::SColor(255,255,255,255), true);
}

void	Graphics::displayBox(const rect_t &box, const color_t &color) const
{
	_driver->draw2DRectangle(irr::video::SColor(color.opacity, color.red,
				color.green, color.blue),
                		irr::core::rect<irr::s32>(box.posX, box.posY,
				box.posX + box.sizeX, box.posY + box.sizeY));
}

void	Graphics::displayText(const std::string &text, const rect_t &rectText,
		const color_t &color)
{
	_font->draw(text.c_str(),
	irr::core::rect<irr::s32>(rectText.posX, rectText.posY, rectText.sizeX,
	rectText.sizeY),
	irr::video::SColor(color.opacity, color.red, color.green, color.blue));
}

bool	Graphics::begin() const
{
	if (_device->run()) {
		_driver->beginScene();
		if (_eventReceiver.isKeyDown(irr::KEY_ESCAPE)) {
			_device->closeDevice();
		}
		return true;
	}
	return false;
}

bool	Graphics::end(void)
{
	if (_device->run()) {
		_smgr->drawAll();
		_guienv->drawAll();
		_driver->endScene();
		if (_eventReceiver.isKeyDown(irr::KEY_ESCAPE)) {
			_device->closeDevice();
		}
		clear_list();
		return true;
	}
	return false;
}

const MyEvent	&Graphics::getEventReceiver(void) const
{
	return _eventReceiver;
}

const std::string	&Graphics::getPath() const
{
	return _path;
}

const std::vector<irr::SEvent::SJoystickEvent>
	&Graphics::getController(void) const
{
	return _eventReceiver.getJoystickState();
}


void	Graphics::initAttribut()
{
	_driver = _device->getVideoDriver();
	_smgr = _device->getSceneManager();
	_guienv = _device->getGUIEnvironment();
	_font = _guienv->getFont(
	(_path + DEFAULT_FONT).c_str());
	_screenSize = _driver->getScreenSize();
	_smgr->addCameraSceneNode(0, irr::core::vector3df(0, 0, 0),
	irr::core::vector3df(0, 0, 100));
	if (!_font) {
		throw MyException("Can't create font");
	}
}

void	Graphics::displayCharacter(const std::vector<ACharacter *> &character,
		const Positions &sizeMap)
{
	auto				playerStruct =
					_playerStruct.begin();
	unsigned int			nbrAlive = 0;

	for (auto it = character.begin(); it != character.end(); it++) {
		while (playerStruct->playerNbr != (*it)->getNbrPlayer()) {
			playerStruct++;
		}
		displayMovingCharacter((*it), playerStruct, sizeMap);
		playerStruct = _playerStruct.begin();
		++nbrAlive;
	}
	if (nbrAlive <  _nbrAlive) {
		 _nbrAlive =  nbrAlive;
		removePlayerStruct(character);
	}
}

void	Graphics::createCharactersNode(const std::vector<ACharacter *>
		&characters, const Positions &sizeMap)
{
	if (characters.size() == 0) {
		throw MyException ("No characters to create");
	}
	for (auto it = characters.begin(); it != characters.end(); it++) {
		_playerStruct.push_back({(*it)->getNbrPlayer(), _nbrAlive,
		IDLE, true});
		displayFirstCharacter(*it, sizeMap);
		++_nbrAlive;
	}
}

void	Graphics::displayFirstCharacter(ACharacter *character,
		const Positions &sizeMap)
{
	std::vector<std::string>		objectPath;
	coord_t					coord;
	irr::scene::IAnimatedMesh		*mesh;

	if (!character) {
		throw MyException("No Character to display");
	}
	objectPath = character->getSprites();
	mesh = _smgr->getMesh((_path + objectPath[0]).c_str());
	if (!mesh) {
			throw MyException("Can't create a mesh");
	}
	coord = createCoord(character->getPos(), sizeMap);
	createAnimeCharacter(mesh, objectPath, coord);
}

void	Graphics::createAnimeCharacter(irr::scene::IAnimatedMesh *mesh,
		const std::vector<std::string> &objectPath,
		const coord_t &coord)
{
	irr::scene::IAnimatedMeshSceneNode	*character;

	character = _smgr->addAnimatedMeshSceneNode(mesh, 0, -1,
	irr::core::vector3df(coord.x, coord.y, coord.z - 0.5),
	irr::core::vector3df(-90,  0, 270),
	irr::core::vector3df(0.05, 0.05, 0.05));
	if (!character) {
		throw MyException("Can't create an animation");
	}
	character->setMD2Animation(STAND);
	character->setMaterialTexture(0, _driver->getTexture((_path +
	objectPath[1]).c_str()));
	character->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_characterNode.push_back(character);
}


void	Graphics::displayMovingCharacter(ACharacter *character,
		std::vector<PlayerStruct>::iterator playerIt,
		const Positions &sizeMap)
{
	if (character->getIsDead() && playerIt->oldAction != 100) {
		_characterNode[playerIt->index]->setMD2Animation(DEAD);
		playerIt->oldAction = static_cast<Action>(100);
	} else if (!character->getIsDead()) {
		displayAliveCharacter(character, playerIt, sizeMap);
	}
}

void	Graphics::removePlayerStruct(const std::vector<ACharacter *> &character)
{
	auto				characterIt =
					character.begin();
	unsigned int			 nbrAlive = 0;

	for (auto it = _playerStruct.begin(); it !=
	_playerStruct.end(); it++) {
		while (nbrAlive < _nbrAlive && (*characterIt)->getNbrPlayer()
		!= it->playerNbr && it->isAlive == true) {
			characterIt++;
			nbrAlive++;
		}
		if (nbrAlive >= _nbrAlive && it->isAlive == true) {
			_characterNode[it->index]->setVisible(false);
			it->isAlive = false;
		}
		characterIt = character.begin();
		nbrAlive = 0;
	}
}

void	Graphics::displayAliveCharacter(ACharacter *character,
		std::vector<PlayerStruct>::iterator playerIt,
		const Positions &sizeMap)
{
	const Action			action = character->getAction();
	const coord_t			coord = createCoord(
					character->getPos(), sizeMap);
	const Action		 	oldAction = playerIt->oldAction;

	if (action == IDLE && oldAction != IDLE) {
		_characterNode[playerIt->index]->setMD2Animation(STAND);
	} else if (action == PUTBOMB && oldAction != PUTBOMB){
		_characterNode[playerIt->index]->setMD2Animation(ATTACK);
	} else {
		if (oldAction != LEFT && oldAction != RIGHT && oldAction != UP
		&& oldAction != DOWN && action != IDLE && action != PUTBOMB) {
			_characterNode[playerIt->index]->setMD2Animation(RUN);
		} else {
			rotateCharacter(oldAction, action, playerIt->index);
			_characterNode[playerIt->index]->setPosition(
			irr::core::vector3df(coord.x, coord.y, coord.z - 0.5));
		}
	}
	playerIt->oldAction = action;
}

void	Graphics::rotateCharacter(const Action oldAction,
		const Action action, const unsigned int index)
{
	if (oldAction == LEFT || oldAction == RIGHT || oldAction == UP
	|| oldAction == DOWN) {
		_characterNode[index]->setRotation(
		irr::core::vector3df(-90, 0, action * -90 - 180));
	}
}

void	Graphics::displayObject(AObject *object, const Positions &sizeMap)
{
	std::string			fullPath;
	Bomb				*bomb;

	if (!object) {
		throw MyException("NULL object received");
	}
	fullPath = _path + object->getLivingSprites();
	if (object->getObjectType() == BOMB) {
		bomb = static_cast<Bomb *>(object);
		bomb->checkTime();
		displayBomb(bomb, sizeMap);
	} else {
		if (object->getIsDestroyed()) {
			fullPath = _path + object->getDyingSprites();
		}
		displayCube(fullPath, object->getPos(), sizeMap);
	}
}

void	Graphics::displayBorder(const std::string &unbWall,
		const Positions &sizeMap)
{
	Positions			borderPos = {-1, -1};

	for (float i = -1; i <= sizeMap.x; i++) {
		for (float j = -1; j <= sizeMap.y; j ++) {
			if (j == -1 || j == sizeMap.y || i == -1 || i == sizeMap.x) {
				displayCube(unbWall, {i, j}, sizeMap);
			}
		}
	}
}

void	Graphics::displayBomb(Bomb *bomb, const Positions &sizeMap)
{
	const std::string		fullPath = _path +
					bomb->getLivingSprites();
	irr::scene::IAnimatedMesh	*mesh;
	const coord_t			coord = createCoord(
					bomb->getPos(),
					sizeMap);

	if (!(bomb->getIsDestroyed())) {
		mesh = _smgr->getMesh(fullPath.c_str());
		if (!mesh) {
			throw MyException("Can't create a mesh");
		}
		displayMeshBomb(mesh, coord, sizeMap);
	} else {
		displayExplosion(bomb, sizeMap);
	}
}

void	Graphics::displayMeshBomb(irr::scene::IAnimatedMesh *mesh,
		const coord_t &coord, const Positions &sizeMap)
{
	irr::scene::IAnimatedMeshSceneNode	*animeBomb;

	animeBomb = _smgr->addAnimatedMeshSceneNode(mesh, 0, -1,
	irr::core::vector3df(coord.x, coord.y , coord.z),
	irr::core::vector3df(90, 0 , 0),
	irr::core::vector3df(MAP_X / sizeMap.x, MAP_Y /
	sizeMap.y, 1));
	if (!animeBomb) {
		throw MyException("Can't create an animation");
	}
	if (std::rand() % 15 != 0) {
		animeBomb->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	}
	_animatedNode.push_back(animeBomb);
}


void	Graphics::displayExplosion(Bomb *bomb, const Positions &sizeMap)
{
	const std::string		fullPath = _path +
					bomb->getDyingSprites();
	const Positions			posBomb = bomb->getPos();
	Positions			posExplosion = posBomb;

	for (unsigned i = bomb->getPower("left"); i > 0; i--) {
		posExplosion.x -= 1;
		displayCube(fullPath, posExplosion, sizeMap);
	}
	posExplosion = posBomb;
	for (unsigned i = bomb->getPower("right"); i > 0; i--) {
		posExplosion.x += 1;
		displayCube(fullPath, posExplosion, sizeMap);
	}
	displayVerticalExplosion(bomb, sizeMap);
}

void	Graphics::displayVerticalExplosion(Bomb *bomb,
		const Positions &sizeMap)
{
	const std::string		fullPath = _path +
					bomb->getDyingSprites();
	const Positions			posBomb = bomb->getPos();
	Positions			posExplosion = posBomb;

	for (unsigned i = bomb->getPower("up"); i > 0; i--) {
		posExplosion.y -= 1;
		displayCube(fullPath, posExplosion, sizeMap);
	}
	posExplosion = posBomb;
	for (unsigned i = bomb->getPower("down"); i > 0; i--) {
		posExplosion.y += 1;
		displayCube(fullPath, posExplosion, sizeMap);
	}
	displayCube(fullPath, posBomb, sizeMap);
}

void	Graphics::displayCube(const std::string &image,
		const Positions &position, const Positions &sizeMap)
{
	coord_t	coord = createCoord(position, sizeMap);
	irr::scene::ISceneNode		*cube = _smgr->addCubeSceneNode(1, 0,
					-1, irr::core::vector3df (coord.x,
					coord.y, coord.z), irr::core::vector3df
					(MAP_Y, 0, 0), irr::core::vector3df
					(MAP_X / sizeMap.x, MAP_Y /
					sizeMap.y, 1));

	setCube(image, cube);
}

void	Graphics::setCube(const std::string &image,
		irr::scene::ISceneNode *cube)
{
	if (cube) {
		cube->setMaterialTexture(0, _driver->getTexture(image.c_str()));
		cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		_sceneNode.push_back(cube);
	} else {
		throw MyException("Can't create a 3D cube");
	}
}

const coord_t	Graphics::createCoord(const Positions &position,
			const Positions &sizeMap) const
{
	const coord_t	coord = {static_cast<float>(position.x * MAP_X /
		sizeMap.x - MAP_X / 2 + 0.5),
		static_cast<float>((position.y * MAP_Y / sizeMap.y - MAP_Y / 2)
		* -1 - 0.5), static_cast<float>(MAP_X - (1 - MAP_Y / MAP_X)
		* position.y)};

	return coord;
}

void	Graphics::clear_list()
{
	for (auto it = _sceneNode.begin(); it != _sceneNode.end(); it++) {
		(*it)->remove();
	}
	for (auto it = _animatedNode.begin(); it != _animatedNode.end(); it++) {
		(*it)->remove();
	}
	for (auto it = _playerStruct.begin(); it != _playerStruct.end(); it++) {
		if (it->isAlive) {
			_characterNode[it->index]->setVisible(false);
		}
	}
	_animatedNode.clear();
	_sceneNode.clear();
}

void	Graphics::reset()
{
	_nbrAlive = 0;
	for (auto it = _characterNode.begin(); it != _characterNode.end();
	it++) {
		(*it)->remove();
	}
	_characterNode.clear();
	_playerStruct.clear();
	_firstTime = true;
}
